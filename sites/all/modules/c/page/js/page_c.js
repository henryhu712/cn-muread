(function($) {

  var pager = 0;
  var term_id = 0;

  /*
  var more_status = 'idle';
  var last_created = 0;

  function show_more_items(newsArr) {
    var $wrapper = $('.main-content-wrapper');
    for (var ix in newsArr) {
      var odd = ix % 2 === 0 ? " news-odd-row" : "";
      var itemHTML = '<div class="news-item-wrap' + odd + '">' +
                       '<div class="news-title">' +
                         '<a href="' + newsArr[ix]['url_origin'] + '">' + newsArr[ix]['title'] + '</a>' +
                       '</div>' +
                       '<div class="news-footer">' + newsArr[ix]['created'] + '</div>' +
                      '</div>';
      $wrapper.append(itemHTML);

    }

    if (newsArr.length < 16) {
      $('#item-more9').hide();
    }
  }
  */


  Drupal.behaviors.muread_articles = {
    attach: function(context, settings) {

      var term_id = settings.page_c.term_id;

      // 更多
      $('#item-more9').on('click', function(e) {

        if ($('#more-spinner').hasClass('hidden') && pager > -1) {

          ++pager;
          $.post('/more', {pageer:pager, term_id:term_id}, function(result) {
            console.log(result);
            $('#more-spinner').addClass('hidden');
          /*
            show_more_items(result.news_array);
            more_status = 'idle';
            last_created = result.last_created;
          */
          }, 'json');

          $('#more-spinner').removeClass('hidden');

        }
      });

    }
  };

})(jQuery);
