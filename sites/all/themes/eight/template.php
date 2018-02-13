<?php
/**
 * @file
 * The primary PHP file for this theme.
 */

/**
 * Implements hook_preprocess_html().
 */
function eight_process_html(&$vars) {

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
