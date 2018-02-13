<?php

/**
 * @file
 */

/**
 * Page c/all
 */
function page_c_all() {

  global $language;

  $page_path = drupal_get_path("module", "page");
  drupal_add_js($page_path . '/js/page_c_all.js');
  drupal_add_css($page_path . '/css/page_c_all.css');

  $data = page_get_articles();

  /*
  drupal_add_js(array('home9Args' => array(
      'lang_prefix' => $language->prefix,
      'last_reddit_id' => $data['last_reddit_id'],
      'last_created' => $data['last_created'],
  )), 'setting');
   */

  $vars = array(
    'article_items' => $data['article_array'],
  );

  return theme('template_c_all', $vars);
}

/**
 * Retrieve all articles.
 */
function page_get_articles($last_created = 0) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'ding_yue_hao')
        ->propertyCondition('status', NODE_PUBLISHED)
        ->propertyOrderBy('created', 'DESC')
        ->addMetaData('account', user_load(1));
  $result = $query->execute();

  $data = array('article_array' => array());
  if (isset($result['node'])) {
    $article_nodes = entity_load('node', array_keys($result['node']));
    foreach ($article_nodes as $article) {
      $created_str = date("Y-m-d", $article->created);
      $data['article_array'][] = array(
        'title' => $article->title,
        'url_origin' => $article->field_url_origin['und'][0]['safe_value'],
        'created' => $created_str,
      );
    }
  }

  return $data;
}

