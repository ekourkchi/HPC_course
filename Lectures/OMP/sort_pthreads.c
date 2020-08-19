<!DOCTYPE html>
<html>
<head profile="http://www.w3.org/1999/xhtml/vocab">
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<link rel="shortcut icon" href="https://www.cilkplus.org/misc/favicon.ico" type="image/vnd.microsoft.icon" />
<meta name="description" content="    Next: Cilk Plus Keywords Introducing Intel® Cilk™ Plus:Extensions to simplify task and data parallelism Intel® Cilk™ Plus adds simple language extensions to the C and C++languages to express task and data parallelism. These language extensions are powerful, yet easy to apply and use in a wide range of applications." />
<meta name="generator" content="Drupal 7 (http://drupal.org)" />
<link rel="canonical" href="https://www.cilkplus.org/cilk-plus-tutorial" />
<link rel="shortlink" href="https://www.cilkplus.org/node/258" />
<meta property="og:site_name" content="CilkPlus" />
<meta property="og:type" content="article" />
<meta property="og:title" content="Cilk Plus Tutorial" />
<meta property="og:url" content="https://www.cilkplus.org/cilk-plus-tutorial" />
<meta property="og:description" content="    Next: Cilk Plus Keywords Introducing Intel® Cilk™ Plus:Extensions to simplify task and data parallelism Intel® Cilk™ Plus adds simple language extensions to the C and C++languages to express task and data parallelism. These language extensions are powerful, yet easy to apply and use in a wide range of applications." />
<meta property="og:updated_time" content="2014-08-27T12:57:28-07:00" />
<meta name="twitter:card" content="summary" />
<meta name="twitter:url" content="https://www.cilkplus.org/cilk-plus-tutorial" />
<meta name="twitter:title" content="Cilk Plus Tutorial" />
<meta name="twitter:description" content="    Next: Cilk Plus Keywords Introducing Intel® Cilk™ Plus:Extensions to simplify task and data parallelism Intel® Cilk™ Plus adds simple language extensions to the C and C++languages to express task and data parallelism. These language extensions are powerful, yet easy to apply and use in a wide range of applications." />
<meta property="article:published_time" content="2012-07-17T10:18:11-07:00" />
<meta property="article:modified_time" content="2014-08-27T12:57:28-07:00" />
<meta itemprop="name" content="Cilk Plus Tutorial" />
<meta itemprop="description" content="    Next: Cilk Plus Keywords Introducing Intel® Cilk™ Plus:Extensions to simplify task and data parallelism Intel® Cilk™ Plus adds simple language extensions to the C and C++languages to express task and data parallelism. These language extensions are powerful, yet easy to apply and use in a wide range of applications." />
<meta name="dcterms.title" content="Cilk Plus Tutorial" />
<meta name="dcterms.creator" content="mad\bmtannen" />
<meta name="dcterms.description" content="    Next: Cilk Plus Keywords Introducing Intel® Cilk™ Plus:Extensions to simplify task and data parallelism Intel® Cilk™ Plus adds simple language extensions to the C and C++languages to express task and data parallelism. These language extensions are powerful, yet easy to apply and use in a wide range of applications." />
<meta name="dcterms.date" content="2012-07-17T10:18-07:00" />
<meta name="dcterms.type" content="Text" />
<meta name="dcterms.format" content="text/html" />
<meta name="dcterms.identifier" content="https://www.cilkplus.org/cilk-plus-tutorial" />
<meta name="dcterms.language" content="und" />
  <title>Cilk Plus Tutorial | CilkPlus</title>
    <link rel="shortcut icon" href="/sites/all/themes/pbb/images/favicon-cilk.ico" type="image/x-icon"> 
  <link type="text/css" rel="stylesheet" href="https://www.cilkplus.org/sites/default/files/css/css_xE-rWrJf-fncB6ztZfd2huxqgxu4WO-qwma6Xer30m4.css" media="all" />
<link type="text/css" rel="stylesheet" href="https://www.cilkplus.org/sites/default/files/css/css_zWfPetBrjxwjs6Iur4IGyOU5Li5P2UPXpPjft7fFsiw.css" media="all" />
<link type="text/css" rel="stylesheet" href="https://www.cilkplus.org/sites/default/files/css/css_Tyxn8wzCd9RnXx9lYdM41plQ1FZR_1_p_itQduSxRLM.css" media="all" />
<link type="text/css" rel="stylesheet" href="https://www.cilkplus.org/sites/default/files/css/css_6RjM2Ji6SCOwF7z0avfjxycSecgIKd-zj3O-eQv9PIo.css" media="all" />
  <script type="text/javascript" src="https://www.cilkplus.org/sites/default/files/js/js_UWQINlriydSoeSiGQxToOUdv493zEa7dpsXC1OtYlZU.js"></script>
<script type="text/javascript" src="https://www.cilkplus.org/sites/default/files/js/js_nT-3TqmhkiIn30tHICx1inWtvQizOLtaBPI9cbRYVJE.js"></script>
<script type="text/javascript" src="https://www.cilkplus.org/sites/default/files/js/js_R9UbiVw2xuTUI0GZoaqMDOdX0lrZtgX-ono8RVOUEVc.js"></script>
<script type="text/javascript" src="https://www.cilkplus.org/sites/default/files/js/js_tgQQ-VzsHltaxXe1xudEqKDyvJTQ6KuRi2INKcYvrZg.js"></script>
<script type="text/javascript">
<!--//--><![CDATA[//><!--
var switchTo5x = true;
//--><!]]>
</script>
<script type="text/javascript" src="https://ws.sharethis.com/button/buttons.js"></script>
<script type="text/javascript">
<!--//--><![CDATA[//><!--
if (stLight !== undefined) { stLight.options({"publisher":"dr-e7ac0-8eec-25fd-ca38-f7a4d4db3af0","version":"5x"}); }
//--><!]]>
</script>
<script type="text/javascript" src="https://www.cilkplus.org/sites/default/files/js/js_rv_BKYv7yieH0IgHddhWHDC-bWGan8yiJbusyOpr0mw.js"></script>
<script type="text/javascript">
<!--//--><![CDATA[//><!--
var _gaq = _gaq || [];_gaq.push(["_setAccount", "UA-17808594-5"]);_gaq.push(['_setCustomVar', 1, "role", "anonymous user", 2]);_gaq.push(["_trackPageview"]);(function() {var ga = document.createElement("script");ga.type = "text/javascript";ga.async = true;ga.src = ("https:" == document.location.protocol ? "https://ssl" : "http://www") + ".google-analytics.com/ga.js";var s = document.getElementsByTagName("script")[0];s.parentNode.insertBefore(ga, s);})();
//--><!]]>
</script>
<script type="text/javascript" src="https://www.cilkplus.org/sites/default/files/js/js_6NgyKymgtYbNoVnzyD-BTrvi0OWEOMthu-gcmZbp6-o.js"></script>
<script type="text/javascript" src="https://www.cilkplus.org/sites/default/files/js/js_zRhY5Pk9J8HQIjIHjfd2wXDpNEotIIxFZtiMN2hJ0Ew.js"></script>
<script type="text/javascript">
<!--//--><![CDATA[//><!--
jQuery.extend(Drupal.settings, {"basePath":"\/","pathPrefix":"","ajaxPageState":{"theme":"pbb","theme_token":"_kKGxMk4UxgscY0VH0X1gNmVlRfv78R7p7GVJV6rTUw","js":{"misc\/jquery.js":1,"misc\/jquery.once.js":1,"misc\/drupal.js":1,"misc\/jquery.cookie.js":1,"misc\/jquery.form.js":1,"misc\/ajax.js":1,"sites\/all\/modules\/admin_menu\/admin_devel\/admin_devel.js":1,"sites\/all\/modules\/custom_search\/js\/custom_search.js":1,"0":1,"https:\/\/ws.sharethis.com\/button\/buttons.js":1,"1":1,"sites\/all\/modules\/google_analytics\/googleanalytics.js":1,"2":1,"sites\/all\/modules\/views\/js\/base.js":1,"misc\/progress.js":1,"sites\/all\/modules\/views\/js\/ajax_view.js":1,"sites\/all\/modules\/views_load_more\/views_load_more.js":1,"sites\/all\/themes\/pbb\/js\/swfobject.js":1,"sites\/all\/themes\/pbb\/js\/pbb.js":1},"css":{"modules\/system\/system.base.css":1,"modules\/system\/system.menus.css":1,"modules\/system\/system.messages.css":1,"modules\/system\/system.theme.css":1,"modules\/comment\/comment.css":1,"sites\/all\/modules\/date\/date_api\/date.css":1,"sites\/all\/modules\/date\/date_popup\/themes\/datepicker.1.7.css":1,"modules\/field\/theme\/field.css":1,"modules\/node\/node.css":1,"modules\/search\/search.css":1,"modules\/user\/user.css":1,"sites\/all\/modules\/views\/css\/views.css":1,"sites\/all\/modules\/ctools\/css\/ctools.css":1,"sites\/all\/modules\/node_embed\/plugins\/node_embed\/node_embed.css":1,"sites\/all\/modules\/panels\/css\/panels.css":1,"sites\/all\/modules\/custom_search\/custom_search.css":1,"sites\/all\/themes\/pbb\/css\/style.css":1}},"custom_search":{"form_target":"_self","solr":0},"googleanalytics":{"trackOutbound":1,"trackMailto":1,"trackDownload":1,"trackDownloadExtensions":"7z|aac|arc|arj|asf|asx|avi|bin|csv|doc|exe|flv|gif|gz|gzip|hqx|jar|jpe?g|js|mp(2|3|4|e?g)|mov(ie)?|msi|msp|pdf|phps|png|ppt|qtm?|ra(m|r)?|sea|sit|tar|tgz|torrent|txt|wav|wma|wmv|wpd|xls|xml|z|zip"},"urlIsAjaxTrusted":{"\/cilk-plus-tutorial":true},"views":{"ajax_path":"\/views\/ajax","ajaxViews":{"views_dom_id:ab9fc7f80b9f488a6ab8cb302d7bd1cf":{"view_name":"software_releases","view_display_id":"block_5","view_args":"","view_path":"node\/258","view_base_path":null,"view_dom_id":"ab9fc7f80b9f488a6ab8cb302d7bd1cf","pager_element":0},"views_dom_id:75b9da8b68fa9226136266354f071949":{"view_name":"software_releases","view_display_id":"block_3","view_args":"","view_path":"node\/258","view_base_path":null,"view_dom_id":"75b9da8b68fa9226136266354f071949","pager_element":0}}}});
//--><!]]>
</script>
    
  <!--[if lte IE 7]>
<!--    <script src="/sites/all/libraries/ie-upgrade/warning.js"></script><script>window.onload=function(){e("/sites/all/libraries/ie-upgrade/")}</script> -->
    <style type="text/css">
      #_d, #_l {
        z-index: 1015;
      }
    </style>
  <![endif]-->

</head>
<body class="html not-front not-logged-in no-sidebars page-node page-node- page-node-258 node-type-page domain-dev-cilk-com" >
  <div id="skip-link">
    <a href="#main-content" class="element-invisible element-focusable">Skip to main content</a>
  </div>
    
<div id="top-bar-wrapper">
  <div id="top-bar">
    <div id="site-logo-wrapper">
      <a href="/" title="Home" rel="home">
        <img id="site-logo-cilk" src="/sites/all/themes/pbb/images/bird-cilk.png" alt="home" />
      </a>
    </div>
  
    <div id="main-menu">
        <div class="region region-main-menu">
    <div id="block-menu-menu-main-menu-cilk" class="block block-menu">

    
  <div class="content">
    <ul class="menu"><li class="first expanded active-trail"><a href="/which-license" target="_top" class="active-trail"><span class="your_class">Learn</span></a><ul class="menu"><li class="first leaf active-trail"><a href="/cilk-plus-tutorial" title="An introduction to using Intel Cilk Plus" class="active-trail active">Tutorial</a></li>
<li class="leaf"><a href="/which-license">Which License is Right for Me?</a></li>
<li class="leaf"><a href="/which-license#gcc-development">Cilk Plus in GCC</a></li>
<li class="leaf"><a href="/which-license#llvm-development">Cilk Plus in LLVM/Clang</a></li>
<li class="leaf"><a href="/cilk-documentation-full">Documentation</a></li>
<li class="leaf"><a href="http://software.intel.com/en-us/code-samples/intel-c-compiler/application-domains" target="_blank">Sample Applications</a></li>
<li class="leaf"><a href="/faq">FAQ</a></li>
<li class="leaf"><a href="/cilk-history">History</a></li>
<li class="last leaf"><a href="/cilk-plus-trademark-license">Cilk Plus Trademark License</a></li>
</ul></li>
<li class="expanded"><a href="/download" target="_top"><span class="your_class">Download</span></a><ul class="menu"><li class="first leaf"><a href="/download#block-views-cilk-tools-block-1">Cilk Tools</a></li>
<li class="leaf"><a href="/download#contributions">Contributed Code</a></li>
<li class="leaf"><a href="/download#block-views-code-samples-block-1">Code Samples</a></li>
<li class="leaf"><a href="/download#open-specification">Open Specifications</a></li>
<li class="leaf"><a href="/download#runtime-sources">Runtime Sources</a></li>
<li class="leaf"><a href="/download#gcc-development-branch">GCC Binaries</a></li>
<li class="leaf"><a href="/download#cilk-plus-llvm">Clang/LLVM Binaries</a></li>
<li class="last leaf"><a href="/download#experimental-software">Experimental Software</a></li>
</ul></li>
<li class="expanded"><a href="/news-archive" target="_top"><span class="your_class">News</span></a><ul class="menu"><li class="first leaf"><a href="/news-archive">News Archive</a></li>
<li class="leaf"><a href="/video-archive">Video Archive</a></li>
<li class="leaf"><a href="/testimonials">Testimonials</a></li>
<li class="leaf"><a href="/papers-and-presentations">Papers and Presentations</a></li>
<li class="leaf"><a href="https://software.intel.com/en-us/blogs" target="_blank">Blogs</a></li>
<li class="last leaf"><a href="https://software.intel.com/en-us/forums/intel-cilk-plus/" target="_blank">Cilk Plus Forum</a></li>
</ul></li>
<li class="expanded"><a href="/submit-cilk-contribution"><span class="your_class">Contribute</span></a><ul class="menu"><li class="first leaf"><a href="/submit-cilk-contribution">Submit Contribution</a></li>
<li class="last leaf"><a href="/contact-us">Contact Us</a></li>
</ul></li>
<li class="last leaf"><a href="/user/login">Login</a></li>
</ul>  </div>
</div>
  </div>
    </div>

      <div class="region region-top-bar">
    <div id="block-search-form" class="block block-search">

    
  <div class="content">
    <form class="search-form" role="search" action="/cilk-plus-tutorial" method="post" id="search-block-form" accept-charset="UTF-8"><div><div class="container-inline">
      <h2 class="element-invisible">Search form</h2>
    <div class="form-item form-type-textfield form-item-search-block-form">
  <input title="Enter the terms you wish to search for." class="custom-search-box form-text" placeholder="Search" type="text" id="edit-search-block-form--2" name="search_block_form" value="" size="15" maxlength="128" />
</div>
<div class="form-item form-type-select form-item-custom-search-types">
  <label for="edit-custom-search-types">Search for </label>
 <select class="custom-search-selector custom-search-types form-select" id="edit-custom-search-types" name="custom_search_types"><option value="c-all" selected="selected">-Any-</option><option value="c-page">Basic page</option><option value="c-code_sample">Code sample</option><option value="c-faq">FAQ</option><option value="c-news">News</option><option value="c-open_specification">Open specification</option><option value="c-plugin">Plugin</option><option value="c-software_release">Software release</option><option value="c-testimonial">Testimonial</option><option value="c-video">Video</option></select>
</div>
<div class="form-actions form-wrapper" id="edit-actions"><input alt="" class="custom-search-button form-submit" type="image" id="edit-submit" name="op" src="/sites/all/themes/pbb/images/searchButton.png" /></div><input type="hidden" name="form_build_id" value="form-2vrzTJv3WXYz2dNfDaACAjdIIQrpw1HYKUJsXAcq51Y" />
<input type="hidden" name="form_id" value="search_block_form" />
</div>
</div></form>  </div>
</div>
  </div>
    
  </div>

</div>
<div id="page" class="site-cilk">

  
<div id="header">

  <div class="intel-title">Intel <sup>&reg;</sup></div>
  <div class="site-acronym">Cilk<sup>&trade;</sup> Plus</div>
  <div class="site-title"></div>
<!-- Do not display version number for Cilk.  Between GCC and the Intel
     compiler, any version we choose would be wrong.

  <div class="header-current-version"><div class="view view-software-releases view-id-software_releases view-display-id-block_5 view-dom-id-ab9fc7f80b9f488a6ab8cb302d7bd1cf">
        
  
  
      <div class="view-content">
        <div class="views-row views-row-1 views-row-odd views-row-first views-row-last">
      
          Version 3 Update 8    </div>
    </div>
  
  
  
  
  
  
</div></div>
-->
  <div id="site-header-image"><img src="/sites/all/themes/pbb/images/bird-illustration-cilk.png" alt="home" /></div>


  <div id="button-site-switch-wrapper">

    <!-- <a href="/compare"> -->
    <a href="http://www.threadingbuildingblocks.org">
      <div id="button-site-switch">
        <img id="button-site-switch-icon" src="/sites/all/themes/pbb/images/bird-tbb-right.png" alt="home" />
        <div id="button-site-switch-text">Would you like to visit TBB?</div>
        <div id="button-site-switch-back"></div>
      </div>
    </a>

    <div id="button-site-switch-description">Intel&reg; TBB is a widely used C++ template library for creating high performance parallel applications.</div>
  </div>

  
<!-- Not TBB - header-download-button-wrapper skipped -->


</div>
  
  <div id="content">
    <div class="tabs"></div>    
        
    <div class="content-1-col clearfix">
      
              <div class="content-box">
          <div class="content-box-header">
                          <h2>Cilk Plus Tutorial</h2>
                      </div>
          <div class="content-box-content">
              <div class="region region-content">
    <div id="node-258" class="node node-page clearfix" about="/cilk-plus-tutorial" typeof="foaf:Document">

  
      <span property="dc:title" content="Cilk Plus Tutorial" class="rdf-meta element-hidden"></span><span property="sioc:num_replies" content="0" datatype="xsd:integer" class="rdf-meta element-hidden"></span>
  
  <div class="content">
    <div class="field field-name-body field-type-text-with-summary field-label-hidden"><div class="field-items"><div class="field-item even" property="content:encoded"><table width="100%"><tbody><tr><td align="right" style="width: 30%; "> </td>
<td style="width: 20%; "> </td>
<td align="left">Next: <a href="tutorial-cilk-plus-keywords">Cilk Plus Keywords</a></td>
</tr></tbody></table><h1>Introducing Intel® Cilk<sup>™</sup> Plus:<br />Extensions to simplify task and data parallelism</h1>
<p>Intel® Cilk<sup>™</sup> Plus adds simple language extensions to the C and C++languages to express task and data parallelism. These language extensions are powerful, yet easy to apply and use in a wide range of applications.</p>
<!--break--><p>Intel Cilk Plus includes the following features and benefits:</p>
<table><thead><tr><th align="left" style="width: 180px">Feature</th>
<th align="left">Benefit</th>
</tr></thead><tbody valign="top"><tr><td>Keywords</td>
<td>Simple, powerful expression of task parallelism:
<ul><li><i>cilk_for</i> - Parallelize for loops</li>
<li><i>cilk_spawn</i> - Specifies that a function can execute in parallel with the remainder of the calling function</li>
<li><i>cilk_sync</i> - Specifies that all spawned calls in a function must complete before execution continues</li>
</ul></td>
</tr><tr><td>Reducers</td>
<td>Eliminate contention for shared variables among tasks by automatically creating views of them as needed and "reducing" them in a lock free manner.</td>
</tr><tr><td>Array Notation</td>
<td>Data parallelism for arrays or sections of arrays.</td>
</tr><tr><td>SIMD-Enabled Functions</td>
<td>Define functions that can be vectorized when called from within an array notation expression or a <code>#pragma simd</code> loop.</td>
</tr><tr><td>#pragma simd</td>
<td>Specifies that a loop is to be vectorized</td>
</tr></tbody></table><h2>Serial Semantics</h2>
<p>A deterministic Intel Cilk Plus application has <em>serial semantics</em>. That is, the result of a parallel run is the same as if the program had executed serially. Serial semantics makes it easier to reason about the parallel application. In addition, developers can use familiar tools to debug the application.</p>
<h2><a href="tutorial-cilk-plus-keywords">Cilk Keywords</a></h2>
<p>Intel Cilk Plus adds three keywords to C and C++ to allow developers to express opportunities for parallelism.</p>
<ul><li><a href="tutorial-cilk-plus-keywords#spawn_and_sync">cilk_spawn</a> - Specifies that a function call can execute asynchronously, without requiring the caller to wait for it to return. This is an expression of an opportunity for parallelism, <em><strong>not</strong></em> a command that mandates parallelism. The Intel Cilk Plus runtime will choose whether to run the function in parallel with its caller.</li>
<li><a href="tutorial-cilk-plus-keywords#spawn_and_sync">cilk_sync</a> - Specifies that all spawned calls in a function must complete before execution continues. There is an implied cilk_sync at the end of every function that contains a cilk_spawn.</li>
<li><a href="tutorial-cilk-plus-keywords#cilk_for">cilk_for</a> - Allows iterations of the loop body to be executed in parallel.</li>
</ul><p>As stated above, the cilk_spawn and cilk_for keywords express <em><strong>opportunites</strong></em> for parallelism. Which portions of your application that actually run in parallel is determined by the Intel Cilk Plus runtime that implements task parallelism with an efficient <a href="tutorial-terms#work-stealing">work-stealing scheduler</a>.</p>
<h2><a href="tutorial-cilk-plus-reducers">Reducers</a></h2>
<p>Intel Cilk Plus includes <em>reducers</em> to help make parallel programming easier. Traditional parallel programs use locks to protect shared variables, which can be problematic.  Incorrect lock use can result in deadlocks.  Contention for locked regions of code can slow a program down.  And while locks can prevent races, there is no way to enforce ordering, resulting in non-deterministic results. Reducers provide a lock-free mechanism that allows parallel code to use private "views" of a variable which are merged at the next sync. The merge is done in an ordered manner  to maintain the serial semantics of the Intel Cilk Plus application.</p>
<h2><a href="tutorial-cilk-tools">Task Parallelism Tools</a></h2>
<p>The Intel Cilk Plus SDK contains race detection and scalability analysis tools for Cilk-style parallelized binaries.  The Cilk tools support code compiled with both the C/C++ compiler from the Intel® Parallel Studio XE tool suites and the GCC "cilkplus" branch C/C++ compiler.</p>
<h2><a href="tutorial-array-notation">Array Notation</a></h2>
<p>Intel Cilk Plus includes a set of notations that allow users to express high-level operations on entire arrays or sections of arrays. These notations help the compiler to effectively <a href="tutorial-terms#vectorize">vectorize</a> the application. Intel Cilk Plus allows C/C++ operations to be applied to multiple array elements in parallel, and also provides a set of builtin functions that can be used to perform vectorized shifts, rotates, and reductions.</p>
<h2><a href="tutorial-simd-enabled-functions">SIMD-Enabled Functions</a></h2>
<p>A SIMD-enabled function is a regular function which can be invoked either on scalar arguments or on array elements in parallel.  They are most useful when combined with array notation or <code>#pragma simd</code>.</p>
<h2><a href="tutorial-pragma-simd">#pragma simd</a></h2>
<p>This pragma gives the compiler permission to <a href="tutorial-terms#vectorize">vectorize</a> a loop even in cases where auto-vectorization might fail. It is the simplest way to manually apply vectorization.</p>
<p> </p>
<table width="100%"><tbody><tr><td align="right" style="width: 30%; "> </td>
<td style="width: 20%; "> </td>
<td align="left">Next: <a href="tutorial-cilk-plus-keywords">Cilk Plus Keywords</a></td>
</tr></tbody></table><p> </p>
</div></div></div>  </div>

  
  
</div>
  </div>
          </div>
          <div class="content-box-footer"></div>
        </div>
                        
    </div>
    
       
    
  </div>
  
  <div id="footer">

  <div id="footer-upper-left">
          <img id="footer-logo" src="/sites/all/themes/pbb/images/bird-cilk-right.png" alt="TBB Bird" />
      <h2>Intel<sup>&reg;</sup> Cilk<sup>&trade;</sup> Plus</h2>
      </div>

  <div id="footer-social-media">
      <div class="region region-footer-social-media">
    <div id="block-sharethis-sharethis-block" class="block block-sharethis">

    
  <div class="content">
    <div class="sharethis-wrapper"><span st_url="https://www.cilkplus.org/cilk-plus-tutorial" st_title="Cilk Plus Tutorial" class="st_facebook"></span>
<span st_url="https://www.cilkplus.org/cilk-plus-tutorial" st_title="Cilk Plus Tutorial" class="st_googleplus"></span>
<span st_url="https://www.cilkplus.org/cilk-plus-tutorial" st_title="Cilk Plus Tutorial" class="st_linkedin"></span>
<span st_url="https://www.cilkplus.org/cilk-plus-tutorial" st_title="Cilk Plus Tutorial" class="st_twitter"></span>
</div>  </div>
</div>
  </div>
    <ul>
      <li><a href="http://www.youtube.com/user/intelswnetwork" class="link-youtube"></a></li>
      <li><a href="http://stackoverflow.com/search?q=cilk" class="link-stack-overflow"></a></li>
      <li><a href="http://sourceforge.net/directory/?q=cilk" class="link-source-forge"></a></li>
      <li><a href="/feed" class="link-rss"></a></li>
    </ul>
  </div>

  <div id="footer-menu-wrapper">
    <h3 class="footer-menu-header">Resources</h3>
    <div id="footer-menu">  <div class="region region-footer-menu">
    <div id="block-menu-menu-footer-menu-cilk" class="block block-menu">

    
  <div class="content">
    <ul class="menu"><li class="first leaf"><a href="/download#block-views-code-samples-block-1">Code Samples</a></li>
<li class="leaf"><a href="/cilk-documentation-full">Documentation</a></li>
<li class="last leaf"><a href="/download">Downloads</a></li>
</ul>  </div>
</div>
  </div>
</div>
  </div>

  <div id="footer-lower-left">
    &copy;Intel Corporation
  </div>

  <div id="footer-copyright-notice">
    Intel and Cilk Plus are trademarks of Intel Corporation in the U.S. and other countries.
  </div>
  
  <div id="footer-menu-left-wrapper">
    <div id="footer-menu-left">  <div class="region region-footer-menu-left">
    <div id="block-menu-menu-footer-menu-left-cilk" class="block block-menu">

    
  <div class="content">
    <ul class="menu"><li class="first leaf"><a href="http://software.intel.com/en-us/articles/optimization-notice" target="_blank">Optimization Notice</a></li>
<li class="leaf"><a href="http://www.intel.com/sites/corporate/tradmarx.htm">Legal Information</a></li>
<li class="leaf"><a href="http://www.intel.com/content/www/us/en/privacy/intel-online-privacy-notice-summary.html" target="_blank">Privacy</a></li>
<li class="leaf"><a href="http://www.intel.com/content/www/us/en/legal/terms-of-use.html" target="_blank">Terms of Use</a></li>
<li class="last leaf"><a href="/sitemap">Site Map</a></li>
</ul>  </div>
</div>
  </div>
</div>
  </div>

  <div id="footer-lower-right">
    Brought to you by
  </div>
  
  <div id="footer-menu-right-wrapper">
    <div id="footer-menu-right"></div>
  </div>

</div>
  
</div>  </body>
</html>
