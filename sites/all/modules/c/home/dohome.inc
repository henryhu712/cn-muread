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

  $data = home_get_collection_of_NewsLink_data(0, $language->language);

  drupal_add_js(array('news_args' => array(
      'lang_code' => $language->language,
      'lang_prefix' => $language->prefix,
      'item_array' => $data,
  )), 'setting');

  $vars = array(
    'news_array' => $data,
  );
*/

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'ding_yue_hao')
        ->propertyCondition('status', NODE_PUBLISHED)
        ->propertyOrderBy('created', 'DESC')
        ->count()
        ->addMetaData('account', user_load(1));
  $number = $query->execute();


  $vars['number_ding_yue_hao'] = $number;

  // Webform
  $block = module_invoke('webform', 'block_view', 'client-block-5364');
  $vars['webform_paste_url'] = render($block['content']);

  return theme('template_home', $vars);
}


/**
 * Create a node of ding yue hao
 */
function home_create_ding_yue_hao($page, $url) {
  preg_match('/var msg_cdn_url = \"([^\"]*)\"/', $page, $m_url, PREG_OFFSET_CAPTURE);
  preg_match('/var msg_title = \"([^\"]*)\"/', $page, $m_title, PREG_OFFSET_CAPTURE);
  preg_match('/var msg_desc = \"([^\"]*)\"/', $page, $m_desc, PREG_OFFSET_CAPTURE);
  preg_match('/var publish_time = \"([^\"]*)\"/', $page, $m_time, PREG_OFFSET_CAPTURE);

  $node = new stdClass();

  $node->title = $m_title[1][0];
  $node->type = 'ding_yue_hao';
  node_object_prepare($node);

  $node->language = 'en';
  $node->uid = 1;
  $node->status = 1;
  $node->field_url_origin[LANGUAGE_NONE][]['value'] = $url;

  if ($file_url = $m_url[1][0]) {
    $file_tmp = file_get_contents($file_url);
    $file_name = 'abc.jpg';
    $file_tmp = file_save_data($file_tmp, 'public://gzh/' . $file_name, FILE_EXISTS_RENAME);
    $node->field_image[LANGUAGE_NONE][] = array(
          'fid' => $file_tmp->fid,
          'filename' => $file_tmp->filename,
          'filemime' => $file_tmp->filemime,
          'uid' => 1,
          'uri' => $file_tmp->uri,
          'status' => 1,
          'display' => 1,
    );
  }

  if ($date = $m_time[1][0]) {
    $node->field_published_date['und'][]['value'] = strtotime($date);
  }

  $node = node_submit($node);
  node_save($node);

}
