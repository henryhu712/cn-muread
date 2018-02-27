<?php

/**
 * @file
 * Front page.
 */

/**
 * Home
 */
function home_content() {

  global $user;

  $vars = array();

/*
  $thepath = drupal_get_path("module", "home");
  drupal_add_js($thepath . '/js/n_more.js');
  drupal_add_css($thepath . '/css/news.css');

  drupal_add_js(array('news_args' => array(
      'lang_code' => $language->language,
      'lang_prefix' => $language->prefix,
      'item_array' => $data,
  )), 'setting');
*/

  // Total
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'ding_yue_hao')
        ->propertyCondition('status', NODE_PUBLISHED)
        ->propertyOrderBy('created', 'DESC')
        ->count()
        ->addMetaData('account', user_load(1));
  $number = $query->execute();

  $vars['number_ding_yue_hao'] = $number;

  // Categories
  $quer2 = new EntityFieldQuery();
  $quer2->entityCondition('entity_type', 'taxonomy_term')
        ->entityCondition('bundle', 'category')
        ->addMetaData('account', user_load(1));
  $result2 = $quer2->execute();

  $vars['terms'] = array();
  if (!empty($result2['taxonomy_term'])) {
    $tids = array_keys($result2['taxonomy_term']);
    $terms = entity_load('taxonomy_term', $tids);
    foreach ($terms as $term) {
      $alias = '';
      if (isset($term->field_alias['und'])) {
	      $alias = $term->field_alias['und'][0]['safe_value'];
      }
      $vars['terms'][] = array(
        'name' => $term->name,
        'alias' => $alias,
      );
    }
  }

  return theme('template_home', $vars);
}


