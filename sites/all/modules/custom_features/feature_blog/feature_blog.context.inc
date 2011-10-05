<?php
/**
 * @file
 * feature_blog.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function feature_blog_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'blogs';
  $context->description = 'Bundle the blogs into a blog sections';
  $context->tag = 'Content';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'blog' => 'blog',
        'blog/*' => 'blog/*',
      ),
    ),
  );
  $context->reactions = array();
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Bundle the blogs into a blog sections');
  t('Content');
  $export['blogs'] = $context;

  return $export;
}
