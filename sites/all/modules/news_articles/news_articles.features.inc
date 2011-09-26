<?php
/**
 * @file
 * news_articles.features.inc
 */

/**
 * Implements hook_node_info().
 */
function news_articles_node_info() {
  $items = array(
    'news' => array(
      'name' => t('News'),
      'base' => 'node_content',
      'description' => t('News articles'),
      'has_title' => '1',
      'title_label' => t('Headline'),
      'help' => '',
    ),
  );
  return $items;
}
