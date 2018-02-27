  <div class="container">
    <div class="row">
      <div class="col-xs-12 col-sm-8 col-sm-offset-2">
        <div class="row">
          <div class="col-xs-4">
            <?php foreach ($terms as $term): ?>
            <div class="term-wrap">
              <a href="/c/<?php print $term['alias']; ?>">
                <?php print $term['name']; ?>
              </a>
            </div>
            <?php endforeach; ?>
          </div>
        </div>
      </div>
    </div>
    <div class="row">
      <div class="col-sm-8">
        <div class="items-container text-center">
          <a href="/c/all">
            全部推荐文章： <?php print $number_ding_yue_hao; ?>
          </a>
        </div>
      </div>
<!--
      <div class="col-sm-4">
关注公众号：必读推荐

      </div>
-->
    </div>
  </div>


