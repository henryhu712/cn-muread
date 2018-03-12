<?php

/**
 * /test
 */
function page_test() {

  global $user;
  if ($user->uid !== 1) {
    return 'error';
  }

  $out = 'kk';
  //return $out;

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'ding_yue_hao')
        ->addMetaData('account', user_load(1));
  $result = $query->execute();
  if (isset($result['node'])) {
    $nodes = entity_load('node', array_keys($result['node']));
    $html_obj = new simple_html_dom();
    foreach ($nodes as $node) {
      //$node->language = 'zh-hans';

      $url = $node->field_url_origin[LANGUAGE_NONE][0]['value'];
      $html_obj->load($url);
      $content = $html_obj->find('div#js_content', 0)->innertext;
      $node->body['zh-hans'][0]['value'] = $content;
      $node->body['zh-hans'][0]['format'] = 'full_html';
      node_save($node);
      $html_obj->clear();
    }
    unset($html_obj);
  }

  return $out;
}

