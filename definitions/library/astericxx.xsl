<?xml version = "1.0" encoding = "UTF-8"?>
<xsl:stylesheet version = "1.0" 
   xmlns:xsl = "http://www.w3.org/1999/XSL/Transform">    
<xsl:output method="html" omit-xml-declaration="yes"/>
   <xsl:template match = "/"> 
#ifndef LIB_ASTERICXX_HPP
#define LIB_ASTERICXX_HPP

#include "IDatablock.hpp"
     <xsl:for-each select = "datablocks/*">
#include "<xsl:value-of select="name()"/>.hpp"
     </xsl:for-each>

namespace astericxx {
     <xsl:for-each select = "datablocks/*">
typedef IDatablock<xsl:text disable-output-escaping="yes">&lt;</xsl:text><xsl:value-of select="name()"/><xsl:text disable-output-escaping="yes">&gt;</xsl:text> Datablock<xsl:value-of select="name()"/>;
     </xsl:for-each>

} // end of namespace astericxx

#endif
   </xsl:template>  
</xsl:stylesheet>