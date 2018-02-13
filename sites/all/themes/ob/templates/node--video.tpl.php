<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php
    // Hide comments, tags, and links now so that we can render them later.
    hide($content['comments']);
    hide($content['links']);
    hide($content['field_tags']);
    //print render($content);
  ?>
  <div class="row">
    <div class="col-sm-9">
      <div id="player-wrapper" class="embed-responsive embed-responsive-16by9">
        <div id="iplayer" class="embed-responsive-item"></div>

  <iframe id="player" type="text/html" allowFullScreen="allowFullScreen" width="640" height="390" class="embed-responsive-item"
  src="https://www.youtube.com/embed/<?php print $the_video_id; ?>?enablejsapi=1&origin=https://muread.com&cc_load_policy=1&cc_lang_pref=<?php print $lang_code; ?>"
  frameborder="0"></iframe>
      </div>
      <div id="subtitle-zone" class="text-center"></div>

      <h1><a href="<?php print $origin_url; ?>"><?php print $title; ?></a></h1>

      <div class="desc-content">
        <?php print render($content['body']); ?>
      </div>

      <?php if (!empty($video_subtitle)): ?>
      <h3><?php print t('Subtitle'); ?></h3>
      <div class="subtitle-content pre-scrollable">
        <?php print $video_subtitle; ?>
      </div>
      <?php endif; ?>

      <div class="social-share-links">
        <?php print $social_share; ?>
      </div>

    </div>
    <div class="col-sm-3">
      <script async src="//pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script>
      <!-- Video -->
      <ins class="adsbygoogle"
         style="display:block"
         data-ad-client="ca-pub-6898386841159675"
         data-ad-slot="3051009644"
         data-ad-format="auto"></ins>
      <script>
        (adsbygoogle = window.adsbygoogle || []).push({});
      </script>
    </div>
  </div>


<script>
      // 2. This code loads the IFrame Player API code asynchronously.
      var tag = document.createElement('script');

      tag.src = "https://www.youtube.com/iframe_api";
      var firstScriptTag = document.getElementsByTagName('script')[0];
      firstScriptTag.parentNode.insertBefore(tag, firstScriptTag);

      // 3. This function creates an <iframe> (and YouTube player)
      //    after the API code downloads.
      var player;
      function onYouTubeIframeAPIReady() {
        player = new YT.Player('player', {
          //height: '480',//'390',
          //width: '854',//'640',
          //videoId: 'dtbcDrhuzbY',
          //videoId: '<?php print $the_video_id; ?>', //'dtbcDrhuzbY',
          events: {
            'onReady': onPlayerReady,
            'onStateChange': onPlayerStateChange
          }
        });

      }
      /*
       */


      // 4. The API will call this function when the video player is ready.
      function onPlayerReady(event) {
        event.target.playVideo();
      }

      // 5. The API calls this function when the player's state changes.
      //    The function indicates that when playing a video (state=1),
      //    the player should play for six seconds and then stop.
      var done = false;

      var subtitle_num = 1;

      function onPlayerStateChange(event) {
        if (event.data == YT.PlayerState.PLAYING && !done) {
          //setTimeout(stopVideo, 26000);
          done = true;

          //setTimeout(showCurrentTime, 200);



          /*
        var subtitles = parser.fromSrt(jQuery.mu_file_content, true);

        for (var i in subtitles) {
                        subtitles[i] = {
                                start : subtitles[i].startTime / 1000,
                                end   : subtitles[i].endTime / 1000,
                                text  : subtitles[i].text
                        };
                }

        var youtubeExternalSubtitle = new YoutubeExternalSubtitle.Subtitle(document.getElementById('player'), subtitles);
 */


        }
      }
      function stopVideo() {
        player.stopVideo();
      }

      // Show subtitle
      function showCurrentTime() {
        //var player = document.getElementById("player");
        var c_time = Math.floor( parseFloat(player.getCurrentTime()) * 1000 );
        var stat = 1;
        //var c_time = player.getCurrentTime() :Number;

        while (1) {

          if (subtitle_num > jQuery.mu_video_data.length) { break; }

          var sub_start = parseInt(jQuery.mu_video_data[ subtitle_num ].start);
          var sub_end   = parseInt(jQuery.mu_video_data[ subtitle_num ].end);
          var sub_text  = jQuery.mu_video_data[ subtitle_num ].text;
          //console.log( c_time + 'st: ' + sub_end + ' tx: ' + sub_text );

          if (c_time > sub_end) {
            subtitle_num++;
            stat++;
            continue;
          }
          else if (c_time > sub_start && stat > 0) {
            var new_text = jQuery.mu_video_data[ subtitle_num ].text;
            jQuery('#subtitle-zone').empty().text(new_text);
          }
          //console.log('no');
          break;
        }

        setTimeout(showCurrentTime, 300);
      }

    </script>


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
