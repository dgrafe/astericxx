<?xml version = "1.0" encoding = "UTF-8"?>
<xsl:stylesheet version = "1.0" 
   xmlns:xsl = "http://www.w3.org/1999/XSL/Transform">  
<xsl:import href="item-extended-length-part.xsl" />
<xsl:output method="html" omit-xml-declaration="yes"/>   
  <xsl:template name = "ExtendedLengthItemType" match="/ExtendedLength">
  <xsl:apply-templates select="/ExtendedLength/Part"/>

<!-- Create the class definition from the template -->
class  <xsl:value-of select="/ExtendedLength/@name"/> : public IExtendedLength {

public:
   <xsl:value-of select="/ExtendedLength/@name"/> () {

   <xsl:for-each select = "/ExtendedLength/*">
   this-<xsl:text disable-output-escaping="yes">&gt;</xsl:text>addItemToSequence(<xsl:text disable-output-escaping="yes">&amp;</xsl:text><xsl:value-of select="@part_name"/>);
   </xsl:for-each>
  }

  // copy constructor making sure that the profile information
  // is created.
  <xsl:value-of select="/ExtendedLength/@name"/>(const <xsl:value-of select="/ExtendedLength/@name"/><xsl:text disable-output-escaping="yes">&amp;</xsl:text> other) : <xsl:value-of select="/ExtendedLength/@name"/>() {

   <xsl:for-each select = "/ExtendedLength/*">
   this-<xsl:text disable-output-escaping="yes">&gt;</xsl:text><xsl:value-of select="@part_name"/> = other.<xsl:value-of select="@part_name"/>;
   </xsl:for-each>
  }

  // assignment operator copying over the contents
  <xsl:value-of select="/ExtendedLength/@name"/><xsl:text disable-output-escaping="yes">&amp;</xsl:text> operator=(const <xsl:value-of select="/ExtendedLength/@name"/><xsl:text disable-output-escaping="yes">&amp;</xsl:text> other) { 
  
      <xsl:for-each select = "/ExtendedLength/*">
       this-<xsl:text disable-output-escaping="yes">&gt;</xsl:text><xsl:value-of select="@part_name"/> = other.<xsl:value-of select="@part_name"/>;
      </xsl:for-each>
  }

  // comparison operators
  bool operator==(<xsl:value-of select="/ExtendedLength/@name"/><xsl:text disable-output-escaping="yes">&amp;</xsl:text> other) { 

  <xsl:for-each select = "/ExtendedLength/*">
       if (this-<xsl:text disable-output-escaping="yes">&gt;</xsl:text><xsl:value-of select="@part_name"/> != other.<xsl:value-of select="@part_name"/>)
          return false;
      </xsl:for-each>
      return true;
  }

  // comparison operators
  bool operator!=(<xsl:value-of select="/ExtendedLength/@name"/><xsl:text disable-output-escaping="yes">&amp;</xsl:text> other) { 

     return !operator==(other);
  }

   // The components of the compound
   <xsl:for-each select = "/ExtendedLength/Part">
   <xsl:value-of select="@name"/><xsl:text> </xsl:text><xsl:value-of select="@part_name"/>;
   </xsl:for-each>

private:
   // Spare components are just placeholders and are not accessible
   <xsl:for-each select = "/ExtendedLength/Spare">
   <xsl:value-of select="@class"/><xsl:text> </xsl:text><xsl:value-of select="@part_name"/>;
   </xsl:for-each>
};

  </xsl:template>  
</xsl:stylesheet>