<xsl:template match="/">
<xsl:text disable-output-escaping='yes'>&lt;!DOCTYPE html></xsl:text>

<html id="html">

	<head>
		<xsl:call-template name="XaGuiHead"/>
    </head>

	<body id="body">
		
		<div class="container" style="left:0;top:0">
			<form style="height:99%" class="form form-1-column" id="Login" name="Login" method="POST" action="?obj=XaUser&amp;evt=Login">

				<fieldset>
						<legend class="LogHomePage" style="line-height:2em" ><img height="50vh" src="/{$GuiStyle}/XAllegroLogo.svg" /></legend>
						<ul>
							<li>
								You have been successfully logged out.
							</li>
							
							<li>
								Click <a href="?">here</a> to log in again.
							</li>

						</ul>
				</fieldset>
			</form>
		</div>
		
		
		
		
    </body>

</html>
</xsl:template>