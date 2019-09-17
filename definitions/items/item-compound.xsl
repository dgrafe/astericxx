<?xml version = "1.0" encoding = "UTF-8"?>
<xsl:stylesheet version = "1.0" 
   xmlns:xsl = "http://www.w3.org/1999/XSL/Transform">  
<xsl:import href="item-fixed-length.xsl" />
<xsl:output method="html" omit-xml-declaration="yes"/>   
  <xsl:template name = "CompoundDataItemType" match="/compound">
  <xsl:apply-templates select="/compound/FixedLength"/>

<!-- Create the class definition from the template -->
class  <xsl:value-of select="/compound/@name"/> : public IFSPEC {

public:
   <xsl:value-of select="/compound/@name"/> () {

   <xsl:for-each select = "/compound/*">
   this-<xsl:text disable-output-escaping="yes">&gt;</xsl:text>addItemToProfile(<xsl:text disable-output-escaping="yes">&amp;</xsl:text><xsl:value-of select="@component_name"/>);
   </xsl:for-each>
  }

  // copy constructor making sure that the profile information
  // is created.
  <xsl:value-of select="/compound/@name"/>(const <xsl:value-of select="/compound/@name"/><xsl:text disable-output-escaping="yes">&amp;</xsl:text> other) : <xsl:value-of select="/compound/@name"/>() {

   <xsl:for-each select = "/compound/*">
   this-<xsl:text disable-output-escaping="yes">&gt;</xsl:text><xsl:value-of select="@component_name"/> = other.<xsl:value-of select="@component_name"/>;
   </xsl:for-each>
  }

  // assignment operator copying over the contents
  <xsl:value-of select="/compound/@name"/><xsl:text disable-output-escaping="yes">&amp;</xsl:text> operator=(const <xsl:value-of select="/compound/@name"/><xsl:text disable-output-escaping="yes">&amp;</xsl:text> other) { 
  
      <xsl:for-each select = "/compound/*">
       this-<xsl:text disable-output-escaping="yes">&gt;</xsl:text><xsl:value-of select="@component_name"/> = other.<xsl:value-of select="@component_name"/>;
      </xsl:for-each>
  }

  // comparison operators
  bool operator==(<xsl:value-of select="/compound/@name"/><xsl:text disable-output-escaping="yes">&amp;</xsl:text> other) { 

  <xsl:for-each select = "/compound/*">
       if (this-<xsl:text disable-output-escaping="yes">&gt;</xsl:text><xsl:value-of select="@component_name"/> != other.<xsl:value-of select="@component_name"/>)
          return false;
      </xsl:for-each>
      return true;
  }

  // comparison operators
  bool operator!=(<xsl:value-of select="/compound/@name"/><xsl:text disable-output-escaping="yes">&amp;</xsl:text> other) { 

     return !operator==(other);
  }

   // The components of the compound
   <xsl:for-each select = "/compound/FixedLength">
   <xsl:value-of select="@name"/><xsl:text> </xsl:text><xsl:value-of select="@component_name"/>;
   </xsl:for-each>

private:
   // Spare components are just placeholders and are not accessible
   <xsl:for-each select = "/compound/Spare">
   <xsl:value-of select="@class"/><xsl:text> </xsl:text><xsl:value-of select="@component_name"/>;
   </xsl:for-each>
};

  </xsl:template>  
</xsl:stylesheet>