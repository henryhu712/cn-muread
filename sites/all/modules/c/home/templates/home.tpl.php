  <div class="container">

    <div class="row latest-content">
      <div class="col-xs-12 col-sm-8 col-sm-offset-2">
        <div class="main-content-wrapper">
          <?php foreach ($newest_articles as $key => $item): ?>
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

                <?php if (!empty($item['desc'])): ?>
                <div class="news-desc hidden">
                  <span class="desc"><?php print $item['desc']; ?></span>
                </div>
                <?php endif; ?>

                <div class="news-footer">
                  <?php print $item['created']; ?>
                </div>
              </div>
            </div>
          <?php endforeach; ?>
        </div>
      </div>
    </div>

    <div class="row">
      <div class="col-sm-8 col-sm-offset-2 all-items">
        <div class="items-container text-center">
          <a href="/c/all">
            全部文章 (<?php print $number_ding_yue_hao; ?>)
          </a>
        </div>
      </div>
    </div>
    <div class="row">
      <div class="col-xs-12 col-sm-8 col-sm-offset-2">
        <div class="row">
          <?php foreach ($terms as $term): ?>
          <div class="col-xs-3 term-wrap-outer">
            <div class="term-wrap">
              <a href="/c/<?php print $term['alias']; ?>">
                <?php print $term['image']; ?>
                <?php print $term['name']; ?>
               (<?php print $term['count']; ?>)
              </a>
            </div>
          </div>
          <?php endforeach; ?>
        </div>
      </div>
    </div>
  </div>


