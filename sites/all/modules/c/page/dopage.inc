<?php

/**
 * @file
 */

/**
 * Page c/all
 */
function page_c($term = '') {

  global $language;

  $page_path = drupal_get_path("module", "page");
  //drupal_add_js($page_path . '/js/dragend.min.js');
  //drupal_add_js($page_path . '/js/page_c.js');
  drupal_add_css($page_path . '/css/page_c.css');

  $data = page_get_articles();

  /*
  drupal_add_js(array('home9Args' => array(
      'lang_prefix' => $language->prefix,
      'last_reddit_id' => $data['last_reddit_id'],
      'last_created' => $data['last_created'],
  )), 'setting');
   */

  $vars = array(
    'article_items' => $data['article_array'],
  );

  return theme('template_c_all', $vars);
}

/**
 * Retrieve all articles.
 */
function page_get_articles($last_created = 0) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'ding_yue_hao')
        ->propertyCondition('status', NODE_PUBLISHED)
        ->propertyOrderBy('created', 'DESC')
        ->addMetaData('account', user_load(1));
  $result = $query->execute();

  $data = array('article_array' => array());
  if (isset($result['node'])) {
    $article_nodes = entity_load('node', array_keys($result['node']));
    foreach ($article_nodes as $article) {
      $uri = $article->field_image['und'][0]['uri'];
      $image_field = field_view_field('node', $article, 'field_image',
        array('settings' => array('image_style' => '100-100')));

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

      $data['article_array'][] = array(
        'title' => $article->title,
        'image' => $image_field,
        'url_origin' => $article->field_url_origin['und'][0]['safe_value'],
        'created' => $published,
        'author' => $author,
        'desc' => $desc,
      );
    }
  }

  return $data;
}


define ("TOKEN", "570fe89ef6");

class wechatCallbackapiTest {

  public function valid() {

    $echoStr = $_GET["echostr"];

    //valid signature , option
    if($this->checkSignature()){
      echo $echoStr;
      exit;
    }
  }

  public function responseMsg($postObj, $fromUsername, $toUsername, $keyword) {
    $time = time();
    $textTpl = "<xml>
                                                        <ToUserName><![CDATA[%s]]></ToUserName>
                                                        <FromUserName><![CDATA[%s]]></FromUserName>
                                                        <CreateTime>%s</CreateTime>
                                                        <MsgType><![CDATA[%s]]></MsgType>
                                                        <Content><![CDATA[%s]]></Content>
                                                        <FuncFlag>0</FuncFlag>
                                                        </xml>";             
    if(!empty( $keyword ))
                {
                        $msgType = "text";
                        $contentStr = $keyword;
                        $resultStr = sprintf($textTpl, $fromUsername, $toUsername, $time, $msgType, $contentStr);
                        echo $resultStr;
                }else{
                        echo "Input something...";
                }

  }
                
        private function checkSignature()
        {
        // you must define TOKEN by yourself
        if (!defined("TOKEN")) {
            throw new Exception('TOKEN is not defined!');
        }
        
        $signature = $_GET["signature"];
        $timestamp = $_GET["timestamp"];
        $nonce = $_GET["nonce"];
                        
                $token = TOKEN;
                $tmpArr = array($token, $timestamp, $nonce);
        // use SORT_STRING rule
                sort($tmpArr, SORT_STRING);
                $tmpStr = implode( $tmpArr );
                $tmpStr = sha1( $tmpStr );
                
                if( $tmpStr == $signature ){
                        return true;
                }else{
                        return false;
                }
        }
}

/**
 * Wechat port.
 */
function page_wechat_port() {
  $wechatObj = new wechatCallbackapiTest();
  $wechatObj->valid();
  drupal_exit();
}
