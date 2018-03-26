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

  $thepath = drupal_get_path("module", "home");
  drupal_add_css($thepath . '/css/home.css');

/*
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

      $uri = $term->field_image['und'][0]['uri'];
      $image_field = field_view_field('taxonomy_term', $term, 'field_image',
        array('settings' => array('image_style' => '110-110')));
      $image_html = render($image_field);

      $count = home_get_number_of_ding_yue_hao_in_a_term($term->tid);

      $vars['terms'][] = array(
        'name' => $term->name,
        'alias' => $alias,
        'image' => $image_html,
        'count' => $count,
      );
    }
  }

  $vars['newest_articles'] = home_get_newest();

  return theme('template_home', $vars);
}

/**
 * Get number
 */
function home_get_number_of_ding_yue_hao_in_a_term($tid) {

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'ding_yue_hao')
        ->propertyCondition('status', NODE_PUBLISHED)
        ->fieldCondition('field_categories', 'target_id', $tid)
        ->count()
        ->addMetaData('account', user_load(1));
  $number = $query->execute();
  return $number;
}


/**
 * Retrieve newest articles.
 */
function home_get_newest() {

  $data = array();

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'ding_yue_hao')
        ->propertyCondition('status', NODE_PUBLISHED)
        ->propertyOrderBy('created', 'DESC')
        ->range(0, 4)
        ->addMetaData('account', user_load(1));
  $result = $query->execute();

  if (isset($result['node'])) {
    $article_nodes = entity_load('node', array_keys($result['node']));
    foreach ($article_nodes as $article) {
      if (mb_strlen($article->title) > MAX_TITLE_LENGTH) {
        $title = mb_substr($article->title, 0, MAX_TITLE_LENGTH, 'UTF-8') . '...';
      }
      else {
        $title = $article->title;
      }

      $uri = $article->field_image['und'][0]['uri'];
      $image_field = field_view_field('node', $article, 'field_image',
        array('settings' => array('image_style' => '160-120')));
      $image_html = render($image_field);

      $published = '';
      if (isset($article->field_published_date['und'])) {
        $published = date('Y-m-d', $article->field_published_date['und'][0]['value']);
      }

      $desc = '';
      if (isset($article->field_desc['und'])) {
        $desc = $article->field_desc['und'][0]['value'];
      }

      $author = '';
      if (isset($article->field_author['und'])) {
        $author = $article->field_author['und'][0]['value'];
      }

      $data[] = array(
        'title' => $title,
        'image' => $image_html,
        'url_origin' => $article->field_url_origin['und'][0]['safe_value'],
        'url_node' => '/' . drupal_get_path_alias('node/' . $article->nid),
        'created' => $published,
        'author' => $author,
        'desc' => $desc,
      );
    }
  }
//  ddl($data);
  return $data;
}


