<!--
<nav class="navbar navbar-default<?php print $fixed_bottom; ?>">
<div class="container" style="margin-top:8px; padding-left:30px;">
  <div class="row">
    <div class="text-center">
      <span style="margin-right:30px;">
    <button type="button" class="btn btn-info" data-toggle="modal" data-target="#ob_cate">
      <?php print t('Categories'); ?>
    </button>
      </span>
      <span>
    <a href="/about">
      <?php //print t('About'); ?>
    </a>
      </span>
    </div>
  </div>
</div>
</nav>
-->

<footer class="footer">
  <nav class="navbar navbar-default">
    <div class="container">
      <div class="row">
        <div class="col-xs-12 col-sm-12 col-md-3 col-md-offset-4 text-center">
          <div class="copyright">
            <span>&copy; 2017 Obserbot LLC</span>
          </div>
        </div>
      </div>
    </div>
  </nav>
</footer>

<div class="modal fade" tabindex="-1" role="dialog" id="ob_cate">
  <div class="modal-dialog" role="document">
    <div class="modal-content">
    <form action="/" method="GET">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
        <h4 class="modal-title"><?php print t('Categories'); ?></h4>
      </div>
      <div class="modal-body">
<!--
        <div class="checkbox">
          <label>
            <input type="checkbox" name="c[]" checked="checked" value=1> TED
          </label>
        </div>
-->
        <div class="checkbox">
          <label>
            <input type="checkbox" name="c[]" checked="checked" value=2> Medium
          </label>
        </div>
        <div class="checkbox">
          <label>
            <input type="checkbox" name="c[]" checked="checked" value=7> <?php print t('Politics'); ?>
          </label>
        </div>
        <div class="checkbox">
          <label>
            <input type="checkbox" name="c[]" checked="checked" value=3> <?php print t('Tech'); ?>
          </label>
        </div>
        <div class="checkbox">
          <label>
            <input type="checkbox" name="c[]" checked="checked" value=4> <?php print t('Entrepreneur'); ?>
          </label>
        </div>
        <div class="checkbox">
          <label>
            <input type="checkbox" name="c[]" checked="checked" value=5> <?php print t('Books'); ?>
          </label>
        </div>
        <div class="checkbox">
          <label>
            <input type="checkbox" name="c[]" checked="checked" value=6> <?php print t('Business'); ?>
          </label>
        </div>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-default" data-dismiss="modal"><?php print t('Cancel'); ?></button>
        <button type="submit" class="btn btn-primary"><?php print t('Submit'); ?></button>
      </div>
    </form>
    </div><!-- /.modal-content -->
  </div><!-- /.modal-dialog -->
</div><!-- /.modal -->



