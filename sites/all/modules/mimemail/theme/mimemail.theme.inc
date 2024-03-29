<?php

/**
 * @file
 * The theme system, which controls the output of the messages.
 */
 
function mimemail_theme_theme() {
  $path = drupal_get_path('module', 'mimemail') . '/theme';

  return array(
    'mimemail_message' => array(
      'variables' => array('key' => NULL, 'recipient' => NULL, 'subject' => NULL, 'body' => NULL),
      'template' => 'mimemail-message',
      'pattern' => 'mimemail_message__',
      'file' => 'mimemail.theme.inc',
      'path' => $path,
    )
  );
}

/**
 * A preprocess function for theme('mimemail_message').
 *
 * The $variables array initially contains the following arguments:
 * - $recipient: The recipient of the message
 * - $key:  The mailkey associated with the message
 * - $subject: The message subject
 * - $body:  The message body
 *
 * @see theme/mimemail-message.tpl.php for additional variables.
 */
function template_preprocess_mimemail_message(&$variables) {
  $theme = variable_get('theme_default', NULL);

  // Fetch the theme for the current domain.
  if (module_exists('domain_theme')) {
    // Assign the selected theme, based on the active domain.
    global $_domain;
    $domain_theme = domain_theme_lookup($_domain['domain_id']);
    // The above returns -1 on failure.
    if ($domain_theme != -1) {
      $theme = $domain_theme['theme'];
    }
  }

  $themepath = drupal_get_path('theme', $theme);

  $sitestyle = variable_get('mimemail_sitestyle', 1);
  $mailstyle = $themepath . '/mail.css';

  // Check for the existence of a mail.css file in the current theme folder.
  if (@file_exists($mailstyle)) {
    $styles = $mailstyle;
  }
  // If no mail.css was found and the site style sheets including is enabled,
  // gather all style sheets and embed a version of all style definitions.
  elseif ($sitestyle) {
    $css_all = drupal_add_css();
    $css_files = array();
    foreach ($css_all as $key => $options) {
      if ($options['group'] == CSS_THEME && $options['type'] == 'file' &&
         ($options['media'] == 'all' || $options['media'] == 'screen')) {
        $css_files[$key] = $options;
      }
    }
    // Grab local.css if it exists (support for Fusion based themes).
    $local = $themepath . '/css/local.css';
    if (@file_exists($local)) {
      $css_files['all']['theme'][$local] = TRUE;
    }
    if (variable_get('preprocess_css', FALSE)) {
      $pattern = '|<link.*href="' . $GLOBALS['base_url'] . '/([^"?]*)[?"].*|';
      $replacement = '\1';
    }
    else {
      $pattern = array(
        '/<([^<>]*)>/', // Remove the style tag.
        '/@import\s+url\("([^"]+)"\);+/', // Remove the import directive.
        '|' . $GLOBALS['base_url'] . '/([^"?]*)[?"].*|' // Remove the base URL.
      );
      $replacement = array('', '\1', '\1');
    }
    $styles = preg_replace($pattern, $replacement, drupal_get_css($css_files));
  }

  // Process each style sheet.
  $css = '';
  foreach (explode("\n", $styles) as $style) {
    if (!empty($style) && @file_exists($style)) {
      $css .= @file_get_contents($style);
    }
  }

  // Regexp to match comment blocks.
  $comment     = '/\*[^*]*\*+(?:[^/*][^*]*\*+)*/';
  // Regexp to match double quoted strings.
  $double_quot = '"[^"\\\\]*(?:\\\\.[^"\\\\]*)*"';
  // Regexp to match single quoted strings.
  $single_quot = "'[^'\\\\]*(?:\\\\.[^'\\\\]*)*'";

  // Perform some safe CSS optimizations (derived from core CSS aggregation).
  $css = preg_replace_callback(
    "<$double_quot|$single_quot|$comment>Sus",  // Match all comment blocks along
    "_mimemail_process_comment",                // with double/single quoted strings
    $css);                                      // and feed them to _mimemail_process_comment().
  $css = preg_replace(
    '<\s*([@{}:;,]|\)\s|\s\()\s*[^\n\S]>S',  // Remove whitespace around separators,
    '\1',                                    // but keep space around parentheses
    $css);                                   // and new lines between definitions.

  // End the file with a new line.
  $css .= "\n";

  // Wordwrap to adhere to RFC821
  $css = wordwrap($css, 700);
  $variables['css'] = $css;

   // Process key to be a proper CSS class.
  $variables['key'] = str_replace('_', '-', $variables['key']);
}

/**
 * Process comment blocks. (derived from core CSS aggregation)
 *
 * This is the callback function for the preg_replace_callback()
 * used in drupal_load_stylesheet_content(). Support for comment
 * hacks is implemented here.
 */
function _mimemail_process_comment($matches) {
  static $keep_nextone = FALSE;
  // Quoted string, keep it.
  if ($matches[0][0] == "'" || $matches[0][0] == '"') {
    return $matches[0];
  }
  // End of IE-Mac hack, keep it.
  if ($keep_nextone) {
    $keep_nextone = FALSE;
    return $matches[0];
  }
  switch (strrpos($matches[0], '\\')) {
    case FALSE :
      // No backslash, strip it.
      return '';
    case drupal_strlen($matches[0])-3 :
      // Ends with \*/ so is a multi line IE-Mac hack, keep the next one also.
      $keep_nextone = TRUE;
      return '/*_\*/';
    default :
      // Single line IE-Mac hack.
      return '/*\_*/';
  }
}
