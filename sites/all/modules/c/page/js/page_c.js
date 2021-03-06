(function($) {

  var pager = 0;
  var term_id = 0;


  function show_more_items(newsArr) {
    var $wrapper = $('.main-content-wrapper');
    for (var ix in newsArr) {
      var odd = ix % 2 === 0 ? " news-odd-row" : "";
      var itemHTML = '<div class="row news-item-wrap' + odd + '">' +
                       '<div class="col-xs-5">' +
                         '<a href="' + newsArr[ix]['url_node'] + '" target="_blank">' +
                           newsArr[ix]['image'] +
                         '</a>' +
                       '</div>' +
                       '<div class="col-xs-7 item-detail">' +
                         '<div class="news-title">' +
                           '<a href="' + newsArr[ix]['url_node'] + '" target="_blank">' +
                             newsArr[ix]['title'] +
                           '</a>' +
                         '</div>' +
                         '<div class="news-footer">' +
                           newsArr[ix]['created'] +
                           //(typeof newsArr[ix]['categories'] !== 'undefined' && newsArr[ix]['categories'].length > 0 ? '<span class="term">' + newsArr[ix]['categories'][0] + '</span>' : '') +
                         '</div>' +
                       '</div>' +
                      '</div>';
      $wrapper.append(itemHTML);
    }

    /*
                           '<a href="' + newsArr['url_node'] + '" target="_blank" class="article-comment">' +
                             '<span class="glyphicon glyphicon-comment" aria-hidden="true"></span>' +
                           '</a>' +
                           */

    if (newsArr.length < 18) {
      $('#item-more9').hide();
    }
  }


  Drupal.behaviors.muread_articles = {
    attach: function(context, settings) {

      var term_id = settings.page_c.term_id;

      // 更多
      $('#item-more9').on('click', function(e) {

        if ($('#more-spinner').hasClass('hidden') && pager > -1) {

          ++pager;
          $.post('/more', {pager:pager, term_id:term_id}, function(result) {
            console.log(result);
            $('#more-spinner').addClass('hidden');
            show_more_items(result.article_array);
          }, 'json');

          $('#more-spinner').removeClass('hidden');

        }
      });

    }
  };

})(jQuery);
