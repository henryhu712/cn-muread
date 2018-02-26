<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <header>
    <span class="submitted">
      <?php print $published; ?>
    </span>
    <span class="submitted">
      <?php print $author; ?>
    </span>
  </header>
  <?php
    // Hide comments, tags, and links now so that we can render them later.
    hide($content['comments']);
    hide($content['links']);
    hide($content['field_tags']);
    kpr($content);
    print render($content);
  ?>
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
