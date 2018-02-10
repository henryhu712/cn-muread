<?php

/**
 * @file
 * Front page.
 */

define( 'TAGS_NUMBER', 20 );

define( 'TIMEBEFORE_NOW',         '现在' );
define( 'TIMEBEFORE_MINUTE',      '{num} 分钟之前' );
define( 'TIMEBEFORE_MINUTES',     '{num} 分钟之前' );
define( 'TIMEBEFORE_HOUR',        '{num} 小时之前' );
define( 'TIMEBEFORE_HOURS',       '{num} 小时之前' );
define( 'TIMEBEFORE_YESTERDAY',   '昨天' );
define( 'TIMEBEFORE_FORMAT',      '%e %b' );
define( 'TIMEBEFORE_FORMAT_YEAR', '%e %b, %Y' );

function time_ago( $time )
{
        $out    = ''; // what we will print out
        $now    = time(); // current time
        $diff   = $now - $time; // difference between the current and the provided dates

        if( $diff < 60 ) // it happened now
            return TIMEBEFORE_NOW;

        elseif( $diff < 3600 ) // it happened X minutes ago
            return str_replace( '{num}', ( $out = round( $diff / 60 ) ), $out == 1 ? TIMEBEFORE_MINUTE : TIMEBEFORE_MINUTES );

        elseif( $diff < 3600 * 24 ) // it happened X hours ago
            return str_replace( '{num}', ( $out = round( $diff / 3600 ) ), $out == 1 ? TIMEBEFORE_HOUR : TIMEBEFORE_HOURS );

        elseif( $diff < 3600 * 24 * 2 ) // it happened yesterday
            return TIMEBEFORE_YESTERDAY;

        else // falling back on a usual date format as it happened later than yesterday
            return strftime( date( 'Y', $time ) == date( 'Y' ) ? TIMEBEFORE_FORMAT : TIMEBEFORE_FORMAT_YEAR, $time );
}


/**
 * Home
 */
function home9() {

  global $language;

  $thepath = drupal_get_path("module", "home");
  drupal_add_js($thepath . '/js/home9.js');
  drupal_add_css($thepath . '/css/home9.css');

  $data = _get_news_items();

  drupal_add_js(array('home9Args' => array(
      'lang_prefix' => $language->prefix,
      'last_reddit_id' => $data['last_reddit_id'],
      'last_created' => $data['last_created'],
  )), 'setting');

  $vars = array(
    'news_items' => $data['news_array'],
  );

  return theme('template_home9', $vars);
}

/**
 * Get new nodes and comments.
 */
function home_get_new_nodes() {

  global $language;
  $lang = $language->language;

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'comment')
      ->propertyOrderBy('created', 'DESC')
      ->range(0, 40)
      ->addMetaData('account', user_load(1));

  $result = $query->execute();

  $data_nids = array();
  $data_comments = array();
  $data = array();

  if (isset($result['comment'])) {
    $cids = array_keys($result['comment']);
    $comments = entity_load('comment', $cids);

    foreach ($comments as $comment) {
      if (in_array($comment->nid, $data_nids)) {
          continue;
      }
      $data_nids[] = $comment->nid;

      $news = node_load($comment->nid);
      $n_wrapper = entity_metadata_wrapper('node', $news);
      $n_wrapper->language($lang);
      $n_title = $n_wrapper->field_mu_title->value();
      $image = '';
      if (!empty($news->field_picture['und'])) {
        $image = theme('image_style', array('style_name' => 'title_image', 'path' => $news->field_picture['und'][0]['uri']));
      }

      $wrapper = entity_metadata_wrapper('comment', $comment);
      $wrapper->language($lang);
      $theComment = $wrapper->comment_body->value();
      $data_comments[] = mb_substr($theComment, 0, 120);

      $data[] = array(
          'news_title' => $n_title,
          'img' => $image,
          'node_url' => url('node/' . $comment->nid, array('language' => $language)),
      );
        //dpm($comment);
    }
  }

  //dpm($data_nids);
  //dpm($data_comments);
  return $data;
}



/**
 * Vidoes
function _home_get_videos($lang) {

  $page = 0;

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'video')
      ->propertyCondition('language', $lang)
      ->propertyOrderBy('created', 'DESC')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->range($page * 8, 4)
      ->addMetaData('account', user_load(1));

  $result = $query->execute();
  $videos = array();
  if (isset($result['node'])) {
    $nids = array_keys($result['node']);
    $videos_items = entity_load('node', $nids);

    foreach ($videos_items as $item) {

      $image = '';
      if (!empty($item->field_picture['und'])) {
        $image = theme('image_style', array('style_name' => 'title_image', 'path' => $item->field_picture['und'][0]['uri']));
      }

      $url = ($lang == 'zh-hans' ? 'zh' : $lang) . url('node/' . $item->nid, array(
            'language' => (object)array('language' => $lang)));

      $title = $item->title;

      $videos[] = array(
          'title' => $title,
          'url' => $url,
          'img' => $image,
      );
    }
  }

  return $videos;
}
 */


/**
 * News
 * @param $page         0, 1, 2, ...
 * @param $lang_code    'en', 'zh-hans', 'es', ...
 */
function home_get_collection_of_NewsLink_data($page, $lang_code = 'en') {

  // How to get language object of Drupal.
  // https://drupal.stackexchange.com/a/68269/24115
  $installed_lang = language_list();
  $lang_obj = $installed_lang[$lang_code];

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'newslink')
      ->fieldOrderBy('field_date', 'value', 'DESC')
      ->propertyOrderBy('promote', 'DESC')
      ->propertyOrderBy('created', 'DESC')
      //->propertyOrderBy('changed', 'DESC')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->range($page * 12, 12)
      ->addMetaData('account', user_load(1));

  $result = $query->execute();
  $news = array();

  if (isset($result['node'])) {
    $nids = array_keys($result['node']);
    $news_items = entity_load('node', $nids);

    $data_for_js = array();

    foreach ($news_items as $item) {

      $image = '';
      $origin_img_url = '';
      if (!empty($item->field_picture['und'])) {
        $image = theme('image_style', array('style_name' => 'title_image', 'path' => $item->field_picture['und'][0]['uri']));
        $origin_img_url = file_create_url($item->field_picture['und'][0]['uri']);
      }

      $bbc_url = isset($item->field_url['und']) ? $item->field_url['und'][0]['value'] : '';

      $wrapper = entity_metadata_wrapper('node', $item);
      $wrapper->language($lang_code);
      $theTitle = $wrapper->field_mu_title->value();

      $item_summary = '';
      if (!empty($item->body)) {
          $item_summary = $wrapper->body->value->value();
      }

      $news_source = $wrapper->field_news_source->value();

      $date = '';
      if (isset($item->field_date['und'])) {
          $date = $item->field_date['und'][0]['value'];
          $date = substr($date, 0, count($date) - 10);
      }

      if ($lang_code == 'ar' && isset($item->field_date['und'])) {
          $initDate = substr($item->field_date['und'][0]['value'], 2, 8);
          $initTimestamp = strtotime($initDate);
          $date = get_arabic_date($initDate, $initTimestamp);
      }

      // Node link
      //$comment_link = url('node/' . $item->nid, array( 'language' => $lang_obj));

      $news[] = array(
        'news_title' => $theTitle,
        'origin_img_url' => $origin_img_url,
        'img' => $image,
        //'img_url' => file_create_url($item->field_picture['und'][0]['uri']),
        //'post_time' => $time,
        'item_summary' => $item_summary,
        'date' => $date,
        'nid' => $item->nid,
        'node_url' => url('node/' . $item->nid, array('language' => $lang_obj)),
        //'managerLink' => '<a class="edit-item" href="' . url('node/' . $item->nid . '/edit') . '">[Edit]</a>'
         // . '<a class="" href="t?nid=' . $item->nid . '">[Translate]</a>',
        'bbc_url' => $bbc_url,
        'news_source' => $news_source,
        //'comment_url' => $comment_link,
        //'lang_code' => $lang_code == 'zh-hans' ? 'zh' : $lang_code,
      );
    }
  }

  return $news;
}


/**
 * News
 */
function _home_get_news($cate, $page = 0, $lang = 'en', $lang_prefix = 'en') {

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'item')
      ->propertyCondition('language', $lang)
      ->fieldCondition('field_published', 'value', '0', '!=')
      ->fieldOrderBy('field_date', 'value', 'DESC')
      ->propertyOrderBy('promote', 'DESC')
      ->propertyOrderBy('created', 'DESC')
      //->propertyOrderBy('changed', 'DESC')
      //->propertyCondition('status', NODE_PUBLISHED)
      ->range($page * 12, 12)
      ->addMetaData('account', user_load(1));

  if (!empty($cate) && count($cate) < TAGS_NUMBER) {
    $not = array();
    for ($ix=1; $ix<TAGS_NUMBER+1; $ix++) {
      if (!in_array($ix, $cate)) {
        $not[] = $ix;
      }
    }
    $query->fieldCondition('field_tag', 'target_id', $not, 'NOT IN');
  }

  $result = $query->execute();
  $news = array();
  if (isset($result['node'])) {
    $nids = array_keys($result['node']);
    $news_items = entity_load('node', $nids);

    $data_for_js = array();

    foreach ($news_items as $item) {

      //$image = field_view_field('node', $item, 'field_picture');
      //$image = render($image);
      $image = '';
      $origin_img_url = '';
      if (!empty($item->field_picture['und'])) {
        $image = theme('image_style', array('style_name' => 'title_image', 'path' => $item->field_picture['und'][0]['uri']));
        $origin_img_url = file_create_url($item->field_picture['und'][0]['uri']);
      }

      /*
      $time = '';
      if (isset($item->field_seconds['und'])) {
        $howlong = (int)$item->created;
        $time = time_ago($howlong);
      }
       */

      $bbc_url = isset($item->field_origin_url['und']) ? $item->field_origin_url['und'][0]['value'] : '';


      list($linksArr_to_js, $linksArr_html, $linksArr3, $links_html2) = dohome_generate_links($item, $lang);
      $data_for_js[$item->nid] = array(
        'links' => $linksArr_to_js,
        'flags_html' => $links_html2,
      );


      $intro = isset($item->field_intro['und']) ? $item->field_intro['und'][0]['value'] : '';
      $item_summary = isset($item->field_item_summary['und']) ? $item->field_item_summary['und'][0]['value'] : '';

      /*
      $tags = array(array('name' => '', 'href' => ''));
      if (isset($item->field_tag['und'])) {
        $tags = array();
        foreach ($item->field_tag['und'] as $aterm) {
          $term_id = $aterm['target_id'];
          $term = taxonomy_term_load($term_id);
          $translated_term2 = i18n_taxonomy_term_name($term, $lang);

          $arguments = http_build_query(array('c' => array($term_id)));
          $tags[] = array(
            'name' => $translated_term2,
            'href' => 'https://muread.com/' . $lang_prefix . '?' . $arguments,
          );
        }
      }
       */

      $date = '';
      if (isset($item->field_date['und'])) {
          $date = $item->field_date['und'][0]['value'];
          $date = substr($date, 0, count($date) - 10);
      }

      $theTitle = $item->title;
      $itemType = 'news'; //Empty now
      // Summary!
      if (isset($item->field_type['und'])) {

        $theType = $item->field_type['und'][0]['value'];

        if ($theType == '2') {
          $image = '<a href="javascript:;" class="pop-item" data-nid="' . $item->nid .'">' . $image . '</a>';

          $theSummary = isset($item->field_intro['und']) ? strip_tags($item->field_intro['und'][0]['value']) : '';
          $theSummary = isset($item->field_intro['und'][1]) ? $theSummary . '<br>' . strip_tags($item->field_intro['und'][1]['value']) : $theSummary;
          $theTitle = '<a href="javascript:;" class="pop-item pop-item-container" data-nid="' . $item->nid
            . '" data-imgurl="' . $origin_img_url . '" data-originurl="'
            . $bbc_url . '">'
            . '<div class="highlight-title">' . $item->title . '</div><div class="summary-content">'
            . $theSummary . '</div></a>';
          $itemType = 'summary';
        }
        elseif ($theType == '3') {
          $image = '<a href="' . $bbc_url . '" target="_blank">' . $image . '</a>';
          $theTitle = '<a href="' . $bbc_url . '" target="_blank" class="goto_origin" data-nid="' . $item->nid . '">' . $item->title . '</a>';
          $itemType = 'origin';
        }
        elseif ($theType == '4' && isset($item->field_intro['und'])) {
          $image = '<a href="' . $bbc_url . '" target="_blank">' . $image . '</a>';
          $theTitle = '<a href="' . $bbc_url . '" target="_blank" class="goto_origin" data-nid="' . $item->nid . '">' . $item->field_intro['und'][0]['value'] . '</a>';
          $itemType = 'origin';
        }
      }

      if ($lang == 'ar' && isset($item->field_date['und'])) {
          $initDate = substr($item->field_date['und'][0]['value'], 2, 8);
          $initTimestamp = strtotime($initDate);
          $date = get_arabic_date($initDate, $initTimestamp);
      }

      //$hits = empty($item->field_hits['und']) ? 0 : $item->field_hits['und'][0]['value'];

      global $language;

      // Node link
      $comment_link = '';
      $thePrefix = $lang == 'zh-hans' ? 'zh' : $lang;
      if ($item->status == '1') {
          $comment_link = '<a href="' . url('node/' . $item->nid, array(
            'language' => $language)) . '"><span class="glyphicon glyphicon-comment" aria-hidden="true"></span></a>';
      }

      // External link
      /*
      preg_match('/^http[s]?:\/\/[^\/]+\//', $bbc_url, $match);
      $ending = substr($bbc_url, -8);
      $external_link = '<a href="' . $bbc_url . '" target="_blank">' . $match[0] . '...' . $ending . '</a>';
       */

      $news[] = array(
        'title_zh' => $theTitle,
        'origin_img_url' => $origin_img_url,
        'img' => $image,
        //'img_url' => file_create_url($item->field_picture['und'][0]['uri']),
        //'post_time' => $time,
        'item_intro' => $intro,
        'item_summary' => $item_summary,
        //'tags' => $tags,
        'nid' => $item->nid,
        'date' => $date,
        'item_type' => $itemType,
        'managerLink' => '<a class="edit-item" href="' . url('node/' . $item->nid . '/edit') . '">[Edit]</a>'
          . '<a class="" href="t?nid=' . $item->nid . '">[Translate]</a>',
        //'hits' => $hits,
        'links_html' => $linksArr_html,
        'links_html2' => $links_html2,
        'comment_link' => $comment_link,
        'bbc_url' => $bbc_url,
      );
    }
  }

  return array('news_array' => $news, 'data_for_js' => $data_for_js);
}


/**
 * Generate links.
 */
function dohome_generate_links($item, $lang) {

  $linksArr = array();
  $linksArr2 = array();
  $linksArr3 = array();
  $links_html = '';
  $links_html2 = '';

      if (isset($item->field_links['und'])) {
        $links = $item->field_links['und'];
        foreach ($links as $link) {
          $linkNode = node_load((int)$link['target_id']);
          $linkWrapper = entity_metadata_wrapper('node', (int)$link['target_id']);
          //$linkWrapper = entity_metadata_wrapper('node', $linkNode, $info);
 
          // Country colection
          $country_val = $linkWrapper->field_country->value();
          $country_iso2 = empty($country_val) ? 'us' : strtolower($country_val->iso2);
          if (empty($linkArr2[$country_iso2])) {
            $linkArr2[$country_iso2] = array();
          }
         // dpm($country_iso2);

          $linkWrapper2 = $linkWrapper->language($lang);
          $linkTitle = $linkWrapper2->field_link_title->value();
          $linkURL = $linkWrapper2->field_url->value();
          $linkLang = $linkWrapper2->field_source_language->value();
          $linkLang = empty($linkLang) ? 'en' : $linkLang;
          $langName = 'English';
          if ($linkLang != 'en') {
            $ls = language_list('enabled');
            $langName = $ls[1][$linkLang]->native;
          }

          $linkDate = $linkWrapper2->field_date->value();
          $news_date = empty($linkDate) ? '' : date('Y-m-d', $linkDate) . ' ';

          $linksArr[] = array(
            'url' => $linkURL,
            'title' => $linkTitle,
            'news_date' => $news_date,
            'lang_name' => $langName,
            'iso2' => $country_iso2,
          );
          $linksArr2[$country_iso2][] = array(
            'url' => $linkURL,
            'title' => $linkTitle,
            'news_date' => $news_date,
            'lang_name' => $langName,
          );

          /*
          $links_html .= '<div class="muread-link"><span class="glyphicon glyphicon-new-window" aria-hidden="true"></span>['
              . $langName . '] ' . '<a href="' . $linkURL . '" target="_blank">' . $linkTitle . '</a></div>';
           */
        }


        foreach ($linksArr2 as $iso2 => $country_links) {
            usort($country_links, function($a, $b) {
                return strcmp($b['news_date'], $a['news_date']);
            });
            $linksArr3[$iso2] = $country_links;

            $links_html2 .= '<span class="flag-icon flag-icon-' . $iso2 . '" data-iso="' . $iso2 . '"></span>';
        }

        foreach ($linksArr3 as $iso2 => $links) {
            $links_html .= '<div class="links-wrapper links-wrapper-' . $iso2 . '">';
            foreach ($links as $link) {
              $links_html .= '<div class="muread-link"><span class="glyphicon glyphicon-new-window" aria-hidden="true"></span>['
                . $link['news_date'] . '] ' . '<a href="' . $link['url'] . '" target="_blank">' . $link['title'] . '</a></div>';
            }
            $links_html .= '</div>';
        }
        //dpm($linksArr3);

      }

  return array($linksArr, $links_html, $linksArr3, $links_html2);
}


/**
 * Record hits.
function home_hit_origin() {

  $nid = isset($_POST['nid']) ? (int)$_POST['nid'] : -1;
  if ($node = node_load($nid)) {
    $wrapper = entity_metadata_wrapper('node', $node);
    $hits = $wrapper->field_hits->value();
    if (empty($hits)) {
      $wrapper->field_hits->set(1);
    }
    else {
      $wrapper->field_hits->set((int)$hits + 1);
    }
    $wrapper->save();
  }

  $filename = time();
  file_put_contents('/mrbot/' . $filename, 'ok');

  echo 'ok';
  drupal_exit();
}
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

  return theme('template_home', $vars);
}


/**
 * News
function home_news() {

  global $user, $language;

  $isAdmin = 'no';
  foreach ($user->roles as $key => $value) {
    if ($value == 'editor') {
      $isAdmin = 'yes';
      break;
    }
  }

  $thepath = drupal_get_path("module", "home");
  drupal_add_js($thepath . '/js/more.js');
  drupal_add_css($thepath . '/css/home.css');

  // https://github.com/lipis/flag-icon-css
  // Add just the css file and flags/ directory.
  drupal_add_css($thepath . '/css/flag-icon.min.css');

  $cate = array();

  drupal_add_js(array('home_args' => array(
      'lang' => $language->language,
      'lang_prefix' => $language->prefix,
  )), 'setting');

  $data = _home_get_news($cate, 0, $language->language, $language->prefix);
  drupal_add_js(array('data_for_js' => array(
    'item_data' => $data['data_for_js'],
  )), 'setting');

  $vars = array(
    'news_array' => $data['news_array'],
    'isAdmin' => $isAdmin,
  );

  return theme('template_news', $vars);
}
 */


/*
function _home_create_a_news($href, $title, $image_src, $seconds, $intro) {

  global $user;
  if ($user->uid != 1) { return; }

  // Upload image!!!
  $random = drupal_random_key(32);
  $file_path = file_save_data(file_get_contents($image_src), 'public://news_pictures/' . $random . '.jpg');

  // entity_create replaces the procedural steps in the first example of
  // creating a new object $node and setting its 'type' and uid property
  $values = array(
    'type' => 'news',
    'uid' => 1,
    'status' => 1,
    'promote' => 0,
  );
  $entity = entity_create('node', $values);

  // The entity is now created, but we have not yet simplified use of it.
  // Now create an entity_metadata_wrapper around the new node entity
  // to make getting and setting values easier
  $ewrapper = entity_metadata_wrapper('node', $entity);

  // Using the wrapper, we do not have to worry about telling Drupal
  // what language we are using. The Entity API handles that for us.
  $ewrapper->title->set($title);
  $cmd = "trans -b :zh \"" . $title . "\"";
  $trans = shell_exec($cmd);
  $trans = preg_replace('/null$/', '', $trans);

  // Picture
  $ewrapper->field_picture->file->set($file_path);

  // News titles
  $titles = array($title, $trans);
  $ewrapper->field_news_title->set($titles);

  // href
  $ewrapper->field_origin_url->set($href);

  // Seconds
  $ewrapper->field_seconds->set($seconds);

  // Intro
  $cmd2 = "trans -b :zh \"" . $intro . "\"";
  $trans2 = shell_exec($cmd2);
  $trans2 = preg_replace('/null$/', '', $trans2);
  $intros = array($intro, $trans2);
  $ewrapper->field_intro->set($intros);

  // Now just save the wrapper and the entity
  // There is some suggestion that the 'true' argument is necessary to
  // the entity save method to circumvent a bug in Entity API. If there is
  // such a bug, it almost certainly will get fixed, so make sure to check.
  $ewrapper->save();
}
 */


/**
 * Get picture.
 */
function _home_get_news_picture($href) {

  $dom = new DOMDocument;
  $html = file_get_contents($href);
  $dom->loadHTML($html);

  $finder = new DomXPath($dom);
  libxml_use_internal_errors(true);

  $nodes = $finder->query("//div[@class='story-body__inner']");
  $img = $nodes->item(0)->childNodes->item(1)->childNodes->item(0)->childNodes->item(1);
  $src = $img->attributes->getNamedItem('src')->nodeValue;
    /*
    $src ="test";
     */

  $intro_node = $finder->query("//p[@class='story-body__introduction']");
  $intro = $intro_node->item(0)->nodeValue;

  return array($src, $intro);
}


/**
 * Convert into Arabic date formate.
 * https://stackoverflow.com/a/17946727/3054511
 *
 * It seems there is anohter approach for Drupal:
 * https://api.drupal.org/api/drupal/includes%21common.inc/function/format_date/7.x
 */
function get_arabic_date($your_date, $timestamp) {

  $months = array("Jan" => "يناير", "Feb" => "فبراير", "Mar" => "مارس", "Apr" => "أبريل", "May" => "مايو", "Jun" => "يونيو", "Jul" => "يوليو", "Aug" => "أغسطس", "Sep" => "سبتمبر", "Oct" => "أكتوبر", "Nov" => "نوفمبر", "Dec" => "ديسمبر");
  $en_month = date("M", strtotime($your_date));
  foreach ($months as $en => $ar) {
    if ($en == $en_month) { $ar_month = $ar; }
  }

  $find = array ("Sat", "Sun", "Mon", "Tue", "Wed" , "Thu", "Fri");
  $replace = array ("السبت", "الأحد", "الإثنين", "الثلاثاء", "الأربعاء", "الخميس", "الجمعة");
  $ar_day_format = date('D', $timestamp);
  $ar_day = str_replace($find, $replace, $ar_day_format);

  //header('Content-Type: text/html; charset=utf-8');
  $standard = array("0","1","2","3","4","5","6","7","8","9");
  $eastern_arabic_symbols = array("٠","١","٢","٣","٤","٥","٦","٧","٨","٩");
  $current_date = date('d', $timestamp).' / '.$ar_month.' / '.date('Y', $timestamp);
  $arabic_date = str_replace($standard , $eastern_arabic_symbols , $current_date);

  return $arabic_date;
}


/**
 * More entrance
 */
function home_more() {

  $cate = isset($_REQUEST['c']) ? $_REQUEST['c'] : array();
  $page = isset($_REQUEST['page']) ? $_REQUEST['page'] : 0;
  $lang_code = isset($_REQUEST['lang_code']) ? $_REQUEST['lang_code'] : 'en';
  $lang_prefix = isset($_REQUEST['lang_prefix']) ? $_REQUEST['lang_prefix'] : 'en';

  $data = _home_get_news($cate, $page, $lang_code, $lang_prefix);
  //$news_array = $data['news_array'];
  //$news_json = json_encode($news_array);
  $news_json = json_encode($data);
  
  echo $news_json;
  drupal_exit();
}

/**
 * More entrance
 */
function home_nmore() {

  $page = isset($_REQUEST['page']) ? $_REQUEST['page'] : 0;
  $lang_code = isset($_REQUEST['lang_code']) ? $_REQUEST['lang_code'] : 'en';
  $lang_prefix = isset($_REQUEST['lang_prefix']) ? $_REQUEST['lang_prefix'] : 'en';

  $data = home_get_collection_of_NewsLink_data($page, $lang_code, $lang_prefix);
  $news_json = json_encode($data);

  echo $news_json;
  drupal_exit();
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


/**
 * More entrance
 */
function home_more9() {

  $last_created = isset($_REQUEST['last_created']) ? trim($_REQUEST['last_created']) : 0;
  $lang_prefix = isset($_REQUEST['lang_prefix']) ? trim($_REQUEST['lang_prefix']) : '';
  if (empty($last_created) || empty($lang_prefix)) {
    echo json_encode(array('Error 87234'));
    drupal_exit();
  }

  $data = _get_news_items($last_created, $lang_prefix);
  echo json_encode($data);
  drupal_exit();
}


