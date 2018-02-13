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
        <div class="main-image">
  <?php
    // Hide comments, tags, and links now so that we can render them later.
    hide($content['comments']);
    hide($content['links']);
    hide($content['field_tags']);
        print render($content['field_picture']);
    //print render($content['field_item_summary']);
  ?>
        </div>
        <div class="">
          <?php print render($content['field_intro']); ?>
        </div>
        <div class="origin-url">
          <?php print $origin_url; ?>
        </div>
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
    //print render($content);
  ?>
  <?php
    // Only display the wrapper div if there are tags or links.
    $field_tags = render($content['field_tags']);
    $links = render($content['links']);
    if ($field_tags || $links):
  ?>
   <footer>
     <?php //print $field_tags; ?>
     <?php //print $links; ?>
  </footer>
  <?php endif; ?>
  <?php //print render($content['comments']); ?>
</article>
