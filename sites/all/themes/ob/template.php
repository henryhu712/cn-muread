<?php
/**
 * @file
 * The primary PHP file for this theme.
 */

/**
 * Implements hook_preprocess_html().
 */
function ob_process_html(&$vars) {

  // https://www.drupal.org/node/1670822


  // http://stackoverflow.com/a/19207265/3054511
  // There are also issues when add debug such as kpr($vars).
  // I do not know where it is in $vars, may be not included in $vars.
/*
  foreach (array('head', 'styles', 'scripts', 'page_bottom', 'page') as $replace) {
    if (!isset($vars[$replace])) {
      continue;
    }

    $vars[$replace] = preg_replace('/(src|href|@import )(url\(|=)(")http(s?):/', '$1$2$3', $vars[$replace]);
  }
 */

}

/**
 * Implements hook_preprocess_page().
 */
function ob_preprocess_page(&$vars) {

  /*
  $curr_path = current_path();
  global $language;
   */

  $vars['ob_footer'] = _obserbot_footer();
  $vars['nav_footer'] = _nav_footer();
}


/**
 * Implements hook_preprocess_page().
 */
function ob_preprocess_node(&$node) {


  global $language;
  $lang = $language->language;
  //dpm($node);

  if ($node['type'] == 'item') {

      $ls = language_list('enabled');
      //$ls2 = local_language_list('name');
      //dpm($ls2);

    $node['origin_url'] = '';
    if (!empty($node['field_links'])) {
        $links = $node['field_links'];
        foreach ($links as $link) {
          $linkWrapper = entity_metadata_wrapper('node', (int)$link['target_id']);

          // Country
          $country_val = $linkWrapper->field_country->value();
          $country_iso2 = empty($country_val) ? 'us' : strtolower($country_val->iso2);

          $linkWrapper2 = $linkWrapper->language($lang);
          $linkTitle = $linkWrapper2->field_link_title->value();
          $linkURL = $linkWrapper2->field_url->value();

          $linkDate = $linkWrapper2->field_date->value();
          $news_date = empty($linkDate) ? '' : date('Y-m-d', $linkDate) . ' ';

          $linkLang = $linkWrapper2->field_source_language->value();
          $linkLang = empty($linkLang) ? 'en' : $linkLang;
          $langName = 'English';
          if ($linkLang != 'en') {
            $ls = language_list('enabled');
            $langName = $ls[1][$linkLang]->native;
          }
          $langName = '';

          $node['origin_url'] .= '<div class="muread-link"><span class="glyphicon glyphicon-new-window" aria-hidden="true"></span> '
              . '' . $news_date . '<span class="flag-icon flag-icon-' . $country_iso2 . '"></span> '
              . $langName . ' <a href="' . $linkURL . '" target="_blank">' . $linkTitle . '</a></div>';
        }
    }
    else {
      if (!empty($node['field_origin_url'])) {
        $url = $node['field_origin_url'][0]['value'];
        $node['origin_url'] = '<a href="' . $url . '" target="_blank">' . $url . '</a>';
      }
    }
  }
  if ($node['type'] == 'video') {
    $node['the_video_id'] = '';
    if (!empty($node['field_video_id'])) {
      $node['the_video_id'] = $node['field_video_id'][0]['safe_value'];
    }

    $node['lang_code'] = $language->prefix == 'zh' ? 'zh-CN' : $language->prefix;
    if (!empty($node['field_language_code'])) {
      $node['lang_code'] = $node['field_language_code'][0]['value'];
    }

    $node['origin_url'] = '#';
    if (!empty($node['field_url'])) {
      $node['origin_url'] = $node['field_url'][0]['value'];
    }

    $node['social_share'] = ob_easy_social_share_block_HTML();


    $node['video_subtitle'] = '';
    if (!empty($node['field_subtitle_file'])) {
      $filename = drupal_realpath($node['field_subtitle_file'][0]['uri']);

      if ($file = fopen($filename, "r")) {

        $status = "new";
        $subtitle_html = '';
        $num = '';

        while (!feof($file)) {
          $line = trim(fgets($file));
          if (empty($line)) {
            $subtitle_html .= $status == 'time' ? '<br>' : '';
            $status = 'new';
          }
          else if ($status == 'new') {
            $num = $line;
            $status = 'number';
          }
          else if ($status == 'number') {
            $subtitle_html .= '[' . $line . '] ';
            $status = 'time';
          }
          else if ($status == 'time') {
            $subtitle_html .= ' ' . $line;
          }

        }
        fclose($file);

      }
      $node['video_subtitle'] = $subtitle_html;
    }
  }
}


/**
 * Implements hook_theme().
 * For common footer.
 */
function ob_theme($existing, $type, $theme, $path) {

  $theme = array();

  $theme['ob_footer'] = array(
    'template' => 'footer',
    'path' => drupal_get_path('theme', 'ob') . '/templates',
  );
  $theme['nav_footer'] = array(
    'template' => 'nav_footer',
    'path' => drupal_get_path('theme', 'ob') . '/templates',
  );

  return $theme;
}

/**
 * Footer
 */
function _obserbot_footer() {

  $vars = array();

  $vars['fixed_bottom'] = ' navbar-fixed-bottom';
  //$vars['fixed_bottom'] = '';

  return theme('ob_footer', $vars);
}

/**
 * Footer navbar
 */
function _nav_footer() {

  $vars = array();

  return theme('nav_footer', $vars);
}

/*
 * Get social share block HTML.
 */
function ob_easy_social_share_block_HTML() {

  $block = block_load('easy_social', 'easy_social_block_1');
  $render_array = _block_get_renderable_array(_block_render_blocks(array($block)));
  return render($render_array);
}

/**
 * Implements template_preprocess_field().
 * https://drupal.stackexchange.com/a/89699/24115
 */
function ob_preprocess_field(&$vars, $hook) {
  // Add line breaks to plain text textareas.
  if (
    // Make sure this is a text_long field type.
    $vars['element']['#field_type'] == 'text_long'
    // Check that the field's format is set to null, which equates to plain_text.
    && $vars['element']['#items'][0]['format'] == null
  ) {
    $vars['items'][0]['#markup'] = nl2br($vars['items'][0]['#markup']);
  }
}
