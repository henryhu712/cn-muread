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

  $term_info = page_get_term_info($term);
  $data = page_get_articles($term_info['id']);

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
function page_get_articles($term_id = '', $last_created = 0) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'ding_yue_hao')
        ->propertyCondition('status', NODE_PUBLISHED)
        ->propertyOrderBy('created', 'DESC')
        ->addMetaData('account', user_load(1));
  if (!empty($term_id)) {
    $query->fieldCondition('field_categories', 'target_id', $term_id);
  }
  $result = $query->execute();

  $data = array('article_array' => array());
  if (isset($result['node'])) {
    $article_nodes = entity_load('node', array_keys($result['node']));
    foreach ($article_nodes as $article) {
      $uri = $article->field_image['und'][0]['uri'];
      $image_field = field_view_field('node', $article, 'field_image',
        array('settings' => array('image_style' => '160-120')));

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
        'title' => $article->title,
        'image' => $image_field,
        'url_origin' => $article->field_url_origin['und'][0]['safe_value'],
        'created' => $published,
        'author' => $author,
        'desc' => $desc,
        'categories' => $categories,
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

  private function checkSignature() {
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
  /* Validate port
  $wechatObj = new wechatCallbackapiTest();
  $wechatObj->valid();
  drupal_exit();
   */

  $postStr = file_get_contents("php://input");

  if (!empty($postStr)) {
    /* libxml_disable_entity_loader is to prevent XML eXternal Entity Injection,
       the best way is to check the validity of xml by yourself */
    libxml_disable_entity_loader(true);
    $postObj = simplexml_load_string($postStr, 'SimpleXMLElement', LIBXML_NOCDATA);
    //watchdog('77Mrbot', '<pre>' . print_r($postObj, true) . '</pre>');
    $fromUsername = $postObj->FromUserName;
    $toUsername = $postObj->ToUserName;

    $answer = "查看 https://cn.muread.com/c/all";


    if ($postObj->MsgType == 'text') {
      $url = trim($postObj->Content);
      if (strlen($url) > 27 && (substr($url, 0, 27) == 'https://mp.weixin.qq.com/s/' ||
        substr($url, 0, 26) == 'http://mp.weixin.qq.com/s/')) {
        if ($page = file_get_contents($url)) {  
          module_load_include('inc', 'home', 'dohome');
          home_create_ding_yue_hao($page, $url);
          $answer = "成功创建！ https://cn.muread.com/c/all";
        }
      }

      $wechatObj = new wechatCallbackapiTest();
      $wechatObj->responseMsg($postObj, $fromUsername, $toUsername, $answer);
    }
/*
    elseif ($postObj->MsgType == 'event') {
      if ($postObj->Event == 'subscribe') {
        //list($ouid, $bid) = chatbots_log_conversation($fromUsername, $toUsername, 'beginning', '');
      }
    }
 */
  }
  else {
    echo 'Error';
  }

  drupal_exit();
}

/**
 * Configure GongZhongHao menu
 */
function page_wechat_menu_config() {
  // 注释下面的语句，创建自定义菜单
  return 'Empty';

  // 机器人有话说
  $appid = 'wx4bb9a94a41958924';
  $secret = '88a01f61d543b20187801a62ec4c5260';

  $url_token = "https://api.weixin.qq.com/cgi-bin/token?grant_type=client_credential&appid={$appid}&secret={$secret}";
  $reply = drupal_http_request($url_token);
  $data = json_decode($reply->data);

  if ($access_token = $data->access_token) {
    $post_data = '{"button":[
                    {"type":"view",
                     "name":"全部文章",
                     "url":"https://cn.muread.com/c/all"
                    },
                    {"type":"view",
                     "name":"最新消息",
                     "url":"https://muread.com/zh"
                    }
                   ]}';
    $options = array(
      "method" => "POST",
      "data" => $post_data,
      "headers" => array("Content-Type" => "text/xml; charset=UTF-8"),
    );
    $url_menu = "https://api.weixin.qq.com/cgi-bin/menu/create?access_token={$access_token}";
    $result = drupal_http_request($url_menu, $options);
    return $result;
  }
  return 'Error 2';
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
      $cates[] = $term->name;
    }
  }
  return $cates;
}

/**
 * Get Term Id.
 */
function page_get_term_info($term, $get = 'id') {
  $info = array('id' => '', 'name' => '');

  if (!empty($term) && $term != 'all') {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'taxonomy_term')
          ->entityCondition('bundle', 'category')
          ->fieldCondition('field_alias', 'value', $term)
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

