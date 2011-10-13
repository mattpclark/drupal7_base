<?php
/**
 * @file
 * resource_section.features.inc
 */

/**
 * Implements hook_node_info().
 */
function resource_section_node_info() {
  $items = array(
    'resource' => array(
      'name' => t('Resource'),
      'base' => 'node_content',
      'description' => t('Knowledge resources including publications, reports, journal articles, blogs and web sites.'),
      'has_title' => '1',
      'title_label' => t('Resource Title'),
      'help' => '',
    ),
  );
  return $items;
}
