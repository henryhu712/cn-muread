<?php

/**
 * Paste
 */
function page_paste() {
  // Webform
  $block = module_invoke('webform', 'block_view', 'client-block-5364');
  $vars['webform_paste_url'] = render($block['content']);

  return theme('template_paste', $vars);
}

/**
 * Create a node of ding yue hao
 */
function page_create_ding_yue_hao($page, $url, $categories = '') {
  preg_match('/var msg_cdn_url = \"([^\"]*)\"/', $page, $m_url, PREG_OFFSET_CAPTURE);
  preg_match('/var msg_title = \"([^\"]*)\"/', $page, $m_title, PREG_OFFSET_CAPTURE);
  preg_match('/var msg_desc = \"([^\"]*)\"/', $page, $m_desc, PREG_OFFSET_CAPTURE);
  preg_match('/var publish_time = \"([^\"]*)\"/', $page, $m_time, PREG_OFFSET_CAPTURE);
  preg_match('/var nickname = \"([^\"]*)\"/', $page, $m_nickname, PREG_OFFSET_CAPTURE);

  if (!$m_url[1][0] || !$m_url[1][0]) {
    echo 'Error';
    return;
  }

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
    $file_name = random_str(8) . '.jpg';
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

  if ($author = $m_nickname[1][0]) {
    $node->field_author[LANGUAGE_NONE][]['value'] = $author;
  }

  if ($desc = $m_desc[1][0]) {
    $node->field_desc[LANGUAGE_NONE][]['value'] = $desc;
  }

  if (!empty($categories)) {
    $node->field_categories[LANGUAGE_NONE][]['target_id'] = (int)$category;
  }

  $node = node_submit($node);
  node_save($node);
}

/**
 * Generate a random string, using a cryptographically secure 
 * pseudorandom number generator (random_int)
 *
 * For PHP 7, random_int is a PHP core function
 * For PHP 5.x, depends on https://github.com/paragonie/random_compat
 *
 * @param int $length      How many characters do we want?
 * @param string $keyspace A string of all possible characters
 *                         to select from
 * @return string
 *
 * https://stackoverflow.com/a/31107425/3054511
 */
function random_str($length, $keyspace = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ')
{
  $str = '';
  $max = mb_strlen($keyspace, '8bit') - 1;
  for ($i = 0; $i < $length; ++$i) {
    $str .= $keyspace[random_int(0, $max)];
  }
  return $str;
}


