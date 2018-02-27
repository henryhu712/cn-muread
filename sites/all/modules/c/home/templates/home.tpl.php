  <div class="container">
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
          <div class="col-xs-4 term-wrap-outer">
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


