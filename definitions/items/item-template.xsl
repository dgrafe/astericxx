<?xml version = "1.0" encoding = "UTF-8"?>
<xsl:stylesheet version = "1.0" 
   xmlns:xsl = "http://www.w3.org/1999/XSL/Transform">    
<xsl:import href="item-fixed-length.xsl" />
<xsl:import href="item-repetitive.xsl" />
<xsl:import href="item-compound.xsl" />
<xsl:import href="item-extended-length.xsl" />
<xsl:output method="html" omit-xml-declaration="yes"/>
   <xsl:template match = "/"> 
#include "FixedLength.hpp"
#include "RepetitiveDataItem.hpp"
#include "SecondaryPart.hpp"
#include "Spare.hpp"

namespace astericxx {

<xsl:apply-templates />
};
    </xsl:template>  
</xsl:stylesheet>