
-- SUMMARY --

  This is a Mime Mail component module (for use by other modules).
    * It permits users to recieve HTML email and can be used by other modules. The mail
      functionality accepts an HTML message body, mime-endcodes it and sends it.
    * If the HTML has embedded graphics, these graphics are MIME-encoded and included
      as a message attachment.
    * Adopts your site's style by automatically including your theme's stylesheet files in a
      themeable HTML message format
   *  If the recipient's preference is available and they prefer plaintext, the HTML will be
      converted to plain text and sent as-is. Otherwise, the email will be sent in themeable
      HTML with a plaintext alternative.

  For a full description of the module, visit the project page:
    http://drupal.org/project/mimemail

  To submit bug reports and feature suggestions, or to track changes:
    http://drupal.org/project/issues/mimemail


-- REQUIREMENTS --

  Mail System module - http://drupal.org/project/mailsystem


-- INSTALLATION --

  Hopefully, you know the drill by now :)
  1. Download the module and extract the files.
  2. Upload the entire mimemail folder into your Drupal sites/all/modules/
     or sites/my.site.folder/modules/ directory if you are running a multi-site
     installation of Drupal and you want this module to be specific to a
     particular site in your installation.
  3. Enable the Mime Mail module by navigating to:
     Administration > Modules
  4. Adjust settings by navigating to:
     Administration > Configuration > Mime Mail


-- USAGE --

  This module may be required by other modules, but in favor of the recently
  added system actions and Rules integration, it can be useful by itself too.

  Once installed, any module can send MIME-encoded messages by specifing
  MimeMailSystem as the responsible mail system for a particular message
  or all mail sent by one module.

  This can be done through the web by visiting admin/config/system/mailsystem
  or in a program as follows:

  mailsystem_set(array(
    '{$module}_{$key}' => 'MimeMailSystem', // Just messages with $key sent by $module.
    '{$module}' => 'MimeMailSystem', // All messages sent by $module.
  ));

  You can use the following optional parameters to build the e-mail:
    'plain':
      Boolean, whether to send messages in plaintext-only (optional, default is FALSE). 
    'plaintext':
      Plaintext portion of a multipart e-mail (optional).
    'attachments':
      Array of arrays with the path, name and MIME type of the file (optional).
    'headers':
      A keyed array with headers (optional). 

  You can set these in $params either before calling drupal_mail() or in hook_mail()
  and of course hook_mail_alter().

  Normally, Mime Mail uses email addresses in the form of "name" <address@host.com>,
  but PHP running on Windows servers requires extra SMTP handling to use this format.
  If you are running your site on a Windows server and don't have an SMTP solution such
  as the SMTP module installed, you may need to set the 'Use the simple format of
  user@example.com for all email addresses' option on the configuration settings page.

  This module creates a user preference for receiving plaintext-only messages.
  This preference will be honored by all messages if the format is not explicitly set.

  Email messages are formatted using the mimemail-message.tpl.php template.
  This includes a CSS style sheet and uses an HTML version of the text.
  The included CSS is either:
    the mail.css file found in your default theme or
    the combined CSS style sheets of your default theme if enabled.

  To create a custom mail template copy the mimemail-message.tpl.php file from
  the mimemail/theme directory into your default theme's folder. Both general and
  by-mailkey theming can be performed:
    mimemail-message.tpl.php (for all messages)
    mimemail-message--[mailkey].tpl.php (for messages with a specific mailkey)
  Note that if you are using a different administration theme than your default theme,
  you should place the same template files into that theme folder too.

  Images with absolute URL will be available as remote content. To embed images
  into emails you have to use a relative URL or an internal path.
  For example:
    instead of http://www.mysite.com/sites/default/files/mypicture.jpg
    use /home/www/public_html/drupal/sites/default/files/mypicture.jpg
    or /sites/default/files/mypicture.jpg

  Since some email clients (namely Outlook 2007 and GMail) is tend to only regard
  inline CSS, you can use the Compressor to convert CSS styles into inline style
  attributes. It transmogrifies the HTML source by parsing the CSS and inserting the
  CSS definitions into tags within the HTML based on the CSS selectors. To use the
  Compressor, just enable it.


-- CREDITS --

  MAINTAINER: Allie Micka < allie at pajunas dot com >

  * Allie Micka
    Mime enhancements and HTML mail code

  * Gerhard Killesreiter
    Original mail and mime code

  * Robert Castelo
    HTML to Text and other functionality

