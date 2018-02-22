<div id="muread-articles">

    <div class="row home-content">
      <div class="col-xs-12 col-sm-8">
        <div class="main-content-wrapper">
          <?php foreach ($article_items as $key => $item): ?>
            <div class="row news-item-wrap<?php print $key % 2 === 0 ? " news-odd-row" : ""; ?>">
              <div class="col-xs-5">
                <a href="<?php print $item['url_origin']; ?>" target="_blank">
                  <?php print render($item['image']); ?>
                </a>
              </div>
              <div class="col-xs-7 item-detail">
                <div class="news-title">
		  <a href="<?php print $item['url_origin']; ?>" target="_blank">
		    <?php print $item['title']; ?>
                  </a>
                </div>

                <?php if (!empty($item['desc'])): ?>
                <div class="news-desc hidden">
                  <span class="desc"><?php print $item['desc']; ?></span>
                </div>
                <?php endif; ?>

                <?php if (!empty($item['author'])): ?>
                <div class="news-author">
                  <span class="author-nickname"><?php print $item['author']; ?></span>
                </div>
                <?php endif; ?>

                <div class="news-footer">
                  <?php print $item['created']; ?>
                  <?php foreach ($item['categories'] as $category): ?>
                    <span class="term"><?php print $category; ?></span>
                  <?php endforeach; ?>
                </div>
              </div>
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


