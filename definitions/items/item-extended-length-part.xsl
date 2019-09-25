<?xml version = "1.0" encoding = "UTF-8"?>
<xsl:stylesheet version = "1.0" 
   xmlns:xsl = "http://www.w3.org/1999/XSL/Transform">    
<xsl:output method="html" omit-xml-declaration="yes"/>   
  <xsl:template name="ExtendedLengthType" match="Part">

   <!-- Create enums from the xml definition, if any -->
   <xsl:for-each select = "enums/*">
 enum class <xsl:value-of select="local-name()"/> {
     <xsl:for-each select = "*">
        <xsl:value-of select="local-name()"/> = <xsl:value-of select="@value"/>,
     </xsl:for-each>
 };
   </xsl:for-each>

   <!-- Create the class definition from the template -->
class  <xsl:value-of select="@name"/> : public SecondaryPart {


public:
   <xsl:value-of select="@name"/> () 
   : SecondaryPart(<xsl:value-of select="@length"/>) {
   }

   // auto-generated getter/setter
   <xsl:for-each select = "datum">
   // getter for datum <xsl:value-of select="@name"/>:
   <xsl:value-of select="@type"/><xsl:text> </xsl:text><xsl:value-of select="@name"/>() {

      return this-<xsl:text disable-output-escaping="yes">&gt;</xsl:text>getFixedValue<xsl:text disable-output-escaping="yes">&lt;</xsl:text><xsl:value-of select="@type"/><xsl:text disable-output-escaping="yes">&gt;</xsl:text>(<xsl:value-of select="@bits"/>, <xsl:value-of select="@offset"/>, <xsl:value-of select="@mask"/>);
   }

   // setter for datum <xsl:value-of select="@name"/>
   void set<xsl:value-of select="@name"/>(<xsl:value-of select="@type"/> value) {

      this-<xsl:text disable-output-escaping="yes">&gt;</xsl:text>setFixedValue(value, <xsl:value-of select="@bits"/>, <xsl:value-of select="@offset"/>, <xsl:value-of select="@mask"/>);
   }
   </xsl:for-each>
};
  </xsl:template>  
</xsl:stylesheet>