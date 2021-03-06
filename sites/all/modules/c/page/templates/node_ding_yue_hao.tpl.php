<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php if ($contentImageExists): ?>
    <div class="content-image">
      <?php print $content_image; ?>
    </div>
  <?php else: ?>
    <header>
      <span class="submitted">
        <?php print $published; ?>
      </span>
      <span class="submitted">
        <?php print $author; ?>
      </span>
    </header>
    <div class="article-cover">
      <img src="<?php print $image_url; ?>" alt="cover">
    </div>
    <div class="article-body">
      <?php print render($content['body']); ?>
      <?php //print $body_html; ?>
    </div>
  <?php endif; ?>

  <div class="article-origin">
    <a href="<?php print $url_origin; ?>" type="button" class="btn btn-success">阅读原文</a>
  </div>
  <?php
    // Only display the wrapper div if there are tags or links.
    $field_tags = render($content['field_tags']);
    $links = render($content['links']);
    if ($field_tags || $links):
  ?>
   <footer>
     <?php print $field_tags; ?>
     <?php print $links; ?>
  </footer>
  <?php endif; ?>
  <?php //print render($content['comments']); ?>
</article>
