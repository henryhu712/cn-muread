<div id="muread-articles">

    <div class="row breadcrumb-wrap">
      <div class="col-xs-12 col-sm-8 col-sm-offset-2">
        <span class="link-home"><a href="/">首页</a></span> &gt;
        <span class="link-all"><a href="/c/all">全部文章</a></span>
        <?php if (!empty($breadcrumb_2)): ?>
          &gt; <span class="link-cate"><a href="<?php print $breadcrumb_2_path; ?>">
               <?php print $breadcrumb_2; ?>
             </a></span>
        <?php endif; ?>
      </div>
    </div>

    <div class="row home-content">
      <div class="col-xs-12 col-sm-8 col-sm-offset-2">
        <div class="main-content-wrapper">
          <?php foreach ($article_items as $key => $item): ?>
            <div class="row news-item-wrap<?php print $key % 2 === 0 ? " news-odd-row" : ""; ?>">
              <div class="col-xs-5">
                <a href="<?php print $item['url_node']; ?>" target="_blank">
                  <?php print $item['image']; ?>
                </a>
              </div>
              <div class="col-xs-7 item-detail">
                <div class="news-title">
                  <a href="<?php print $item['url_node']; ?>" target="_blank">
                    <?php print $item['title']; ?>
                  </a>
                </div>

                <div class="news-footer">
                  <?php if (!empty($item['author'])): ?>
                    <?php print $item['author']; ?>
                  <?php endif; ?>
    <!--
                  <a href="<?php print $item['url_node']; ?>" target="_blank" class="article-comment">
                    <span class="glyphicon glyphicon-comment" aria-hidden="true"></span> 
                  </a>
-->
                </div>
              </div>
            </div>
          <?php endforeach; ?>
        </div>
      </div>
    </div>

    <?php if ($moreExisting): ?>
    <div id="item-more9" class="row">
      <div class="col-xs-12 col-sm-8 col-sm-offset-2">
        <div class="btn-lg text-center more-wrap">
          <span class="spinner-wrap">
            <span class="spinner hidden" id="more-spinner">
              <img src="../sites/all/modules/c/home/images/spinner.gif" alt="more">
            </span>
            <span class="glyphicon glyphicon-arrow-down" aria-hidden="true"></span>
            <span class="more-text"> 显示更多</span>
          </span>
        </div>
      </div>
    </div>
    <?php endif; ?>

</div>


