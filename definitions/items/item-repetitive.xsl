<?xml version = "1.0" encoding = "UTF-8"?>
<xsl:stylesheet version = "1.0" 
   xmlns:xsl = "http://www.w3.org/1999/XSL/Transform">  
<xsl:import href="item-fixed-length.xsl" />
<xsl:output method="html" omit-xml-declaration="yes"/>   
  <xsl:template name = "RepetitiveDataItemType" match="/repetitive">

<xsl:for-each select = "/repetitive/*">
  <xsl:if test="local-name() = 'FixedLength'">
    <xsl:apply-templates select="/repetitive/FixedLength"/>
  </xsl:if>

<!-- Create the class definition from the template -->
class  <xsl:value-of select="/repetitive/@name"/> : public RepetitiveDataItem<xsl:text disable-output-escaping="yes">&lt;</xsl:text><xsl:value-of select="@name"/><xsl:text disable-output-escaping="yes">&gt;</xsl:text> {

public:
   <xsl:value-of select="/repetitive/@name"/> () {}
};
</xsl:for-each>
  </xsl:template>  
</xsl:stylesheet>