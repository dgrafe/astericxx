<?xml version = "1.0" encoding = "UTF-8"?>
<xsl:stylesheet version = "1.0" 
   xmlns:xsl = "http://www.w3.org/1999/XSL/Transform">    
<xsl:output method="html" omit-xml-declaration="yes"/>
   <xsl:template match = "/"> 
#include "IFSPEC.hpp"
#include "IExtendedLength.hpp"
   <xsl:for-each select = "category/item">
#include "<xsl:value-of select="@filename"/>.hpp"
   </xsl:for-each>

namespace astericxx {

class <xsl:value-of select="/category/@name"/> : public IFSPEC {

public:

  static const uint8_t identifier = <xsl:value-of select="/category/@identifier"/>;
  <xsl:value-of select="/category/@name"/>() {

   <xsl:for-each select = "category/item">
   this-<xsl:text disable-output-escaping="yes">&gt;</xsl:text>addItemToProfile(<xsl:text disable-output-escaping="yes">&amp;</xsl:text><xsl:value-of select="@name"/>);
   </xsl:for-each>
  }

  // copy constructor makinng sure that the profile information
  // is created.
  <xsl:value-of select="/category/@name"/>(const <xsl:value-of select="/category/@name"/><xsl:text disable-output-escaping="yes">&amp;</xsl:text> other) : <xsl:value-of select="/category/@name"/>() {

   <xsl:for-each select = "category/item">
   this-<xsl:text disable-output-escaping="yes">&gt;</xsl:text><xsl:value-of select="@name"/> = other.<xsl:value-of select="@name"/>;
   </xsl:for-each>
  }

  // assignment operator copying over the contents
  <xsl:value-of select="/category/@name"/><xsl:text disable-output-escaping="yes">&amp;</xsl:text> operator=(const <xsl:value-of select="/category/@name"/><xsl:text disable-output-escaping="yes">&amp;</xsl:text> other) { 
  
      <xsl:for-each select = "category/item">
       this-<xsl:text disable-output-escaping="yes">&gt;</xsl:text><xsl:value-of select="@name"/> = other.<xsl:value-of select="@name"/>;
      </xsl:for-each>
  }

  // comparison operators
  bool operator==(<xsl:value-of select="category/@name"/><xsl:text disable-output-escaping="yes">&amp;</xsl:text> other) { 

  <xsl:for-each select = "category/item">
       if (this-<xsl:text disable-output-escaping="yes">&gt;</xsl:text><xsl:value-of select="@name"/> != other.<xsl:value-of select="@name"/>)
          return false;
      </xsl:for-each>
      return true;
  }

  // comparison operators
  bool operator!=(<xsl:value-of select="category/@name"/><xsl:text disable-output-escaping="yes">&amp;</xsl:text> other) { 

     return !operator==(other);
  }
  
   <xsl:for-each select = "category/item">
   <xsl:value-of select="@class"/><xsl:text> </xsl:text><xsl:value-of select="@name"/>;
   </xsl:for-each>
private:
};
  

};
    </xsl:template>  
</xsl:stylesheet>