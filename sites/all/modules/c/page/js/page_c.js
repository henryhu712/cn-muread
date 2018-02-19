(function($) {

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

      //$('#muread-articles').dragend();

      /*
      var last_reddit_id = settings.home9Args.last_reddit_id;
      var lang_prefix = settings.home9Args.lang_prefix;
      last_created = settings.home9Args.last_created;
      */

      // Click More
      /*
      $('#item-more9').on('click', function(e) {

        if ($('#more-spinner').hasClass('hidden') && last_created > 10000) {
          $.post('more9', {last_created:last_created, lang_prefix:lang_prefix}, function(result) {

            console.log(result);
            show_more_items(result.news_array);

            $('#more-spinner').addClass('hidden');
            more_status = 'idle';

            last_created = result.last_created;

          }, 'json');

          $('#more-spinner').removeClass('hidden');
          more_status = 'sending';
        }
      });
      */


      /*
      var html = '';
      var newsItems = Drupal.settings.muread_home.news_items;

      var odd = false;
      for (var ix in newsItems) {
        html += '<div class="news-item-wrap' + (odd ? " news-odd-row" : "") + '"><a href="' +
          newsItems[ix].url_origin + '" target="_blank">' + newsItems[ix].title + '</a></div>';
        odd = !odd;
      }

      $('.main-content-wrapper').append(html);
      */


    }
  };

})(jQuery);
