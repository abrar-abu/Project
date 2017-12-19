<%@page import="checker.Directory"%>
<%@page import="java.io.*"%>
<%@page import="java.util.HashMap"%>
<%@page import="java.util.Map"%>

<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
    <title>Book System</title>

    <!-- Bootstrap -->
    <link href="css/bootstrap.css" rel="stylesheet">
    <link href="css/bootstrap.min.css" rel="stylesheet">
    <link href="css/bootstrap-theme.css" rel="stylesheet">
    <link href="css/bootstrap-theme.min.css" rel="stylesheet">

    <!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/html5shiv/3.7.3/html5shiv.min.js"></script>
      <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    <![endif]-->
    <style type="text/css">
      .carousel-inner img 
      {
        width: 100%;
        max-height: 560px
      }
    </style>
  </head>
  <body>
<!-- 
  <nav class="navbar navbar-default navbar-static-top">
    <div class="container-fluid">
      <div class="navbar-header">
        <a href="" class="navbar-brand">
          <span class="glyphicon glyphicon-search"></span>
          Abrar
        </a>
      </div>
        <div class="nav navbar-nav navbar-right">
           <div class="dropdown">
            <button class="btn btn-defalut dropdown-toggle" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">Dropdown Example
            <span class="caret"></span></button>
            <ul class="dropdown-menu">
              <li><a href="#">HTML</a></li>
              <li><a href="#">CSS</a></li>
              <li><a href="#">JavaScript</a></li>
            </ul>
          </div> 
        </div>
        <ul class="nav navbar-nav navbar-right">
          <li><a href="#">Link</a></li>
          <li class="dropdown">
            <a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-haspopup="true" aria-expanded="false">Dropdown <span class="caret"></span></a>
          <ul class="dropdown-menu">
            <li><a href="#">Action</a></li>
            <li><a href="#">Another action</a></li>
            <li><a href="#">Something else here</a></li>
            <li role="separator" class="divider"></li>
            <li><a href="#">Separated link</a></li>
          </ul>
          </li>
        </ul>
    </div>
    </div>
  </nav> 
-->
  <nav class="navbar navbar-default">
    <div class="container-fluid">
      <div class="navbar-header">
        <a class="navbar-brand" href="#"><span class="glyphicon glyphicon-book"> BookStore</span> </a>
      </div>
      <ul class="nav navbar-nav">
        <li class="active"><a href="GameIndex.html">Home</a></li>
        <li><a href="GamePage1.html">Page 1</a></li>
        <li><a href="GamePage2.html">Page 2</a></li>
      </ul>
      <ul class="nav navbar-nav navbar-right">
        <li><a href="#"><span class="glyphicon glyphicon-user"></span> Sign Up</a></li>
        <li><a href="#"><span class="glyphicon glyphicon-log-in"></span> Login</a></li>
        <li class="dropdown">
          <a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-haspopup="true" aria-expanded="false"><img alt="" class="img-circle" src="avatar3_small.jpg" />Abu<span class="caret"></span></a>
          <ul class="dropdown-menu">
            <li><a href="#">My Profile</a></li>
            <li><a href="#">My Books</a></li>
            <li><a href="#">Performance</a></li>
            <li role="separator" class="divider"></li>
            <li><a href="#">Logout</a></li>
          </ul>
        </li> 
      </ul>
    </div>
  </nav> 
  <H1>Index</H1>
  <div id="carousel-example-generic" class="carousel slide" data-ride="carousel">
  <!-- Indicators -->
  <!-- Wrapper for slides -->
  <div class="carousel-inner" role="listbox" width=100% height=500px>
    <div class="item active">
      <img src="Book3.jpg" alt="...">
      <div class="carousel-caption">
        Books  1
      </div>
    </div>
    <div class="item">
      <img src="Book2.jpg" alt="...">
      <div class="carousel-caption">
        Book  2
      </div>
    </div>
  </div>

  <!-- Controls -->
  <a class="left carousel-control" href="#carousel-example-generic" role="button" data-slide="prev">
    <span class="glyphicon glyphicon-chevron-left" aria-hidden="true"></span>
    <span class="sr-only">Previous</span>
  </a>
  <a class="right carousel-control" href="#carousel-example-generic" role="button" data-slide="next">
    <span class="glyphicon glyphicon-chevron-right" aria-hidden="true"></span>
    <span class="sr-only">Next</span>
  </a>
</div>
	<div class="container well well-lg">
  	<%
		Directory.listDirectory("/home/ubuntu/Downloads/Books/Apptitude/", 0);		
		for(Map.Entry m:Directory.PDFS.entrySet())
		{
	%>
	    <div class="row">
	    <%  
			for(int i=0;i<4;i++)
			{
		%>
			<div class="col-lg-3">
			<div class="card" style="width: 20rem;">
				<img class="card-img-top" src="pdf1.png" height="200px" width=80% alt="Card image cap">
				<div class="card-block">
					<h4 class="card-title"><%=m.getKey()%></h4>
					<a target="_blank" href="<%=m.getKey()%>" class="btn btn-primary">Preview</a>
					<a target="_blank" href="<%=m.getValue()%>" class="btn btn-primary" download>Download</a>
				</div>
			</div>
			</div>
				<%}%>
	    </div>				  
	<%
		}  
	%>
  </div>
	
  <div class="well well-lg">
    <h1>END PAGE</h1>
  </div>
  <!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
    <!-- Include all compiled plugins (below), or include individual files as needed -->
    <script src="js/bootstrap.min.js"></script>
  </body>
</html>