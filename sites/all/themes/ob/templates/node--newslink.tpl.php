<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php if ((!$page && !empty($title)) || !empty($title_prefix) || !empty($title_suffix) || $display_submitted): ?>
  <header>
    <?php print render($title_prefix); ?>
    <?php if (!$page && !empty($title)): ?>
    <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
    <?php endif; ?>
    <?php print render($title_suffix); ?>
    <?php if ($display_submitted): ?>
    <span class="submitted">
      <?php print $user_picture; ?>
      <?php print $submitted; ?>
    </span>
    <?php endif; ?>
  </header>
  <?php endif; ?>

    <div class="row">
      <div class="col-xs-12 col-sm-8">
        <h1><a href="<?php print $mu_url; ?>" target="_blank"><?php print $mu_title; ?></a></h1>

        <img class="img-responsive" src="<?php print $origin_img_url; ?>" alt="">
<?php
    print $mu_body;
    print $mu_news_source;
?>

        <?php print render($content['comments']); ?>
      </div>

      <div class="col-xs-12 col-sm-4">
        <script async src="//pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script>
        <!-- New Muread -->
        <ins class="adsbygoogle"
             style="display:block"
             data-ad-client="ca-pub-6898386841159675"
             data-ad-slot="9125193902"
             data-ad-format="auto"></ins>
            <script>
            (adsbygoogle = window.adsbygoogle || []).push({});
        </script>
      </div>
    </div>

  <?php
    // Hide comments, tags, and links now so that we can render them later.
    hide($content['comments']);
    hide($content['links']);
    hide($content['field_tags']);
    //print render($content);

    global $user, $language;

    if ($user->uid == 1) {
    print '<a href="/' . $language->prefix . '/tr_newslink?nid=' . $node->nid . '">[Translate the newslink title and body - Source language: ' . $language->language . ']</a>';
    }
  ?>
  <?php
    // Only display the wrapper div if there are tags or links.
    $field_tags = render($content['field_tags']);
    $links = render($content['links']);
    if ($field_tags || $links):
  ?>
   <footer>
     <?php print $field_tags; ?>
     <?php //print $links; ?>
  </footer>
  <?php endif; ?>
</article>





      <div><!-- Modal -->
        <div id="pop_news_item" class="modal fade" tabindex="-1" role="dialog">
          <div class="modal-dialog" role="document">
            <div class="modal-content">
              <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                <h4 class="modal-title"></h4>
              </div>
              <div class="modal-body">
                <div id="modal-item-image">
                </div>
                <div id="modal-item-summary">
                </div>
                <div id="modal-item-flags">
                </div>
                <div id="modal-item-origin-url">
                  <span class="news-main-date"></span>
                  <span class="news-main-source"></span>
                </div>
              </div>
              <div class="modal-footer">
                <div class="close-button-wrapper text-center">
                  <button type="button" class="btn btn-info" data-dismiss="modal"><?php print t('Close'); ?></button>
                </div>
              </div>
            </div><!-- /.modal-content -->
          </div><!-- /.modal-dialog -->
        </div>
      </div><!-- End of Modal -->

