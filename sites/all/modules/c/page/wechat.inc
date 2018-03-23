<?php

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
          module_load_include('inc', 'page', 'url_paste');
          page_create_ding_yue_hao($page, $url);
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
                     "name":"分享文章",
                     "url":"https://cn.muread.com/p"
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

