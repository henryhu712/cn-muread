<?php

/**
 * /test
 */
function page_test() {

  $out = 'kk';

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'ding_yue_hao')
        ->addMetaData('account', user_load(1));
  $result = $query->execute();
  if (isset($result['node'])) {
    $nodes = entity_load('node', array_keys($result['node']));
    foreach ($nodes as $node) {
      $node->language = 'zh-hans';
      node_save($node);
      //kpr($node->title);
    }
  }

  return $out;
}

