<div id="muread-articles">
  <div class="dragend-page">

<div class="row home-content">
  <div class="col-xs-12 col-sm-8">
    <div class="main-content-wrapper">
    <?php foreach ($article_items as $key => $item): ?>
      <div class="news-item-wrap<?php print $key % 2 === 0 ? " news-odd-row" : ""; ?>">
        <div class="news-title">
          <a href="<?php print $item['url_origin']; ?>"><?php print $item['title']; ?></a>
        </div>
        <div class="news-footer">
          <?php print $item['created']; ?>
        </div>
        <div class="tt2">go to detail</div>
      </div>
    <?php endforeach; ?>
    </div>

<!--
    <div id="item-more9">
      <div class="btn-lg text-center">
        <span class="spinner-wrap">
          <span class="spinner hidden" id="more-spinner">
            <img src="../sites/all/modules/c/home/images/spinner.gif" alt="">
          </span>
          <span class="glyphicon glyphicon-arrow-down" aria-hidden="true"></span>
          <span class="more-text"> <?php print t('More'); ?></span>
        </span>
      </div>
    </div>
-->
  </div>
</div>

  </div>
  <div class="dragend-page">
<p>test</p>
  </div>
</div>


