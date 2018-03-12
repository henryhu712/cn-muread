<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
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
    <?php //print render($content['body']); ?>
    <?php print $body_html; ?>
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
