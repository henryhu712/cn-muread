
        <div class="row items-container">

        订阅号文章数量： <?php print $number_ding_yue_hao; ?>

        </div>


        <!-- More -->
        <div class="row">
          <div class="col-xs-12 col-sm-12 col-md-12 more-bar">
            <a href="javascript:;" id="item-more">
              <div class="btn-lg text-center">
                <span class="spinner hidden" id="more-spinner"><img src="../sites/all/modules/c/home/images/spinner.gif" alt=""></span>
                <span class="glyphicon glyphicon-arrow-down" aria-hidden="true"></span> <?php print t('More'); ?>
              </div>
            </a>
          </div>
        </div>



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

