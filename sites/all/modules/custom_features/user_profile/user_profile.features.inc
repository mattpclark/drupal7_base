<?php
/**
 * @file
 * user_profile.features.inc
 */

/**
 * Implements hook_default_profile2_type().
 */
function user_profile_default_profile2_type() {
  $items = array();
  $items['profile'] = entity_import('profile2_type', '{
    "userCategory" : true,
    "userView" : true,
    "type" : "profile",
    "label" : "Main profile",
    "weight" : "0",
    "data" : { "registration" : 1 },
    "rdf_mapping" : []
  }');
  return $items;
}
