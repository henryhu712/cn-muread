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

  //$data = _get_news_items();

  /*
  drupal_add_js(array('home9Args' => array(
      'lang_prefix' => $language->prefix,
      'last_reddit_id' => $data['last_reddit_id'],
      'last_created' => $data['last_created'],
  )), 'setting');

  $vars = array(
    'news_items' => $data['news_array'],
  );
   */
  $vars = array();

  return theme('template_home9', $vars);
}

/**
 * Retrieve news data for Javascript.
 *
 * Note: What is the difference of fields() from addField() in db_select()?
 *       It is worth mentioning that if you are trying to ->join() tables that have common field
 *       names and you are wanting to alias them. You will need to add them *individually* with
 *       ->addField()!
 */
function _get_news_items($last_created = 0, $prefix_code = '') {

  /*
  $data = array('news_array' => array());
  $path = '/home/ubuntu/reddit/' . date("Ymd") . '/' . $prefix_code . '/';
  if (!file_exists($path)) {
    $path = '/home/ubuntu/reddit/' . date("Ymd", time() - 60*60*24) . '/' . $prefix_code . '/';
  }
  $files = array_diff(scandir($path, SCANDIR_SORT_DESCENDING), array('.', '..'));

  foreach ($files as $file) {
    $jsonFile = file_get_contents($path . $file);
    $json = json_decode($jsonFile);
    //$content = '<a href="' . $json->url_origin . '" target="_blank">' . $json->title . '</a>';
    //$output .= '<p>'.$content.'</p>';
    $data['news_array'][] = array(
      'title' => $json->title,
      'url_origin' => $json->url_origin,
    );
  }
   */

  global $language;

  // Read from pmuread db.
  db_set_active('external');

  $prefix_code = empty($prefix_code) ? $language->prefix : $prefix_code;
  if ($prefix_code != 'en') {
    $query = db_select('translated', 't');
    $query->join('newsitem', 'n', 't.reddit_id=n.reddit_id');
    $query->addField('t', 'title');
    $query->addField('n', 'url_origin');
    $query->addField('n', 'created');
    $query->condition('t.language', $prefix_code)
      ->orderBy('n.created', 'DESC')
      ->range(0, 16);

    if (!empty($last_created)) {
      $query->condition('n.created', $last_created, '<');
    }

    $result = $query->execute();
  }
  else {
    $query = db_select('newsitem', 'n')
      ->fields('n', array('reddit_id', 'title', 'url_origin', 'created'))
      ->orderBy('created', 'DESC')
      ->range(0, 16);

    /* 上面的写法与下面等价，但是注意: addField()，一次一行！否则要报错。
    $query = db_select('newsitem', 'n');
    $query->addField('n', 'reddit_id');
    $query->addField('n', 'title');
    $query->addField('n', 'url_origin');
    $query->range(0, 15);
     */

    if (!empty($last_created)) {
      $query->condition('n.created', $last_created, '<');
    }

    $result = $query->execute();
  }

  while ($row = $result->fetchAssoc()) {
    $createdTimestamp = $row['created'];
    $created_str = date("Y-m-d H:i", $createdTimestamp) . " UTC";

    if ((int)$createdTimestamp > 1416058368) {
      // http://php.net/manual/en/timezones.php
      // http://php.net/manual/en/timezones.asia.php
      switch ($prefix_code) {
        case 'zh': $timezone = 'Asia/Hong_Kong';    break;
        case 'vi': $timezone = 'Asia/Ho_Chi_Minh';  break;
        case 'ko':
        case 'ja': $timezone = 'Asia/Tokyo';        break;
        default:   $timezone = FALSE;
      }
      if ($timezone) {
        $created_date = new DateTime("@" . $createdTimestamp); // snap to UTC because of the '@timezone' syntax
        $created_date->setTimezone(new DateTimeZone($timezone));
        $created_str = $created_date->format('m-d H:i');
      }
    }

    $data['news_array'][] = array(
      'title' => $row['title'],
      'url_origin' => $row['url_origin'],
      'created' => $created_str,
    );
    $data['last_reddit_id'] = '';
    $data['last_created'] = $createdTimestamp;
  }
  db_set_active();

  return $data;
}


