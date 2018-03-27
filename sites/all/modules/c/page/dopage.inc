<?php

/**
 * @file
 */

define('MAX_ITEMS_ONE_PAGE', 20);

/**
 * Page c/all
 */
function page_c($term_alias = '') {

  $page_path = drupal_get_path("module", "page");
  drupal_add_js($page_path . '/js/page_c.js');
  drupal_add_css($page_path . '/css/page_c.css');

  $term_info = page_get_term_info($term_alias);
  $data = page_get_articles($term_info['id']);

  drupal_add_js(array('page_c' => array(
    'term_id' => $term_info['id'],
  )), 'setting');

  $vars = array(
    'breadcrumb_2' => $term_alias == 'all' ? '' : $term_info['name'],
    'breadcrumb_2_path' => $term_alias == 'all' ? '' : '/c/' . $term_alias,
    'article_items' => $data['article_array'],
    'moreExisting' => count($data['article_array']) < MAX_ITEMS_ONE_PAGE ? FALSE : TRUE,
  );

  return theme('template_c_all', $vars);
}

/**
 * More entrance
 */
function page_more() {

  $pager = isset($_REQUEST['pager']) ? $_REQUEST['pager'] : 0;
  $term_id = isset($_REQUEST['term_id']) ? $_REQUEST['term_id'] : 0;
  if (empty($pager)) {
    echo json_encode(array('Error 87234'));
    drupal_exit();
  }

  $data = page_get_articles($term_id, $pager);
  echo json_encode($data);
  drupal_exit();
}

/**
 * Retrieve all articles.
 */
function page_get_articles($term_id = '', $pager = 0) {

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'ding_yue_hao')
        ->propertyCondition('status', NODE_PUBLISHED)
        ->fieldOrderBy('field_published_date', 'value', 'DESC')
        ->propertyOrderBy('created', 'DESC')
        ->range($pager * MAX_ITEMS_ONE_PAGE, MAX_ITEMS_ONE_PAGE)
        ->addMetaData('account', user_load(1));
  if (!empty($term_id)) {
    $query->fieldCondition('field_categories', 'target_id', $term_id);
  }
  $result = $query->execute();

  $data = array('article_array' => array());
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

      $categories = page_get_categories_array($article);

      $data['article_array'][] = array(
        'title' => $title,
        'image' => $image_html,
        'url_origin' => $article->field_url_origin['und'][0]['safe_value'],
        'url_node' => '/' . drupal_get_path_alias('node/' . $article->nid),
        'created' => $published,
        'author' => $author,
        'desc' => $desc,
        'categories' => $categories,
      );
    }
  }

  return $data;
}


/**
 * Get categories of article
 *
 * Note: debug method:
 * https://www.drupal.org/project/devel/issues/2828328
 * dpm(), kpr(), ddl()
 */
function page_get_categories_array($article) {

  $cates = array();

  if (isset($article->field_categories['und'])) {
    foreach ($article->field_categories['und'] as $cate) {
      $term = taxonomy_term_load($cate['target_id']);
      if (empty($term->field_alias['und'])) {
        $cates[] = $term->name;
      }
      else {
        $alias = $term->field_alias['und'][0]['safe_value'];
        $cates[] = '<a href="/c/' . $alias . '" target="_blank">' . $term->name . '</a>';
      }
    }
  }
  return $cates;
}

/**
 * Get Term information from alias.
 */
function page_get_term_info($term_alias = '') {

  $info = array('id' => '', 'name' => '');

  if (!empty($term_alias) && $term_alias != 'all') {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'taxonomy_term')
          ->entityCondition('bundle', 'category')
          ->fieldCondition('field_alias', 'value', $term_alias)
          ->addMetaData('account', user_load(1));
    $result = $query->execute();

    if (isset($result['taxonomy_term'])) {
      $keys = array_keys($result['taxonomy_term']);
      $terms = entity_load('taxonomy_term', $keys);
      foreach ($terms as $term_obj) {
        $info['id'] = $term_obj->tid;
        $info['name'] = $term_obj->name;
      }
    }
  }

  return $info;
}

