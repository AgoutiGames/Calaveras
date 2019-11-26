<?xml version="1.0" encoding="UTF-8"?>
<tileset name="arrow" tilewidth="256" tileheight="256" tilecount="12" columns="4">
 <image source="arrow.png" width="1024" height="768"/>
 <tile id="0" type="ACTOR_ANIMATION">
  <properties>
   <property name="ACTOR_NAME" value="Arrow"/>
   <property name="ANIMATION_TYPE" value="IDLE"/>
   <property name="DIRECTION" value="NONE"/>
  </properties>
  <animation>
   <frame tileid="0" duration="100"/>
   <frame tileid="1" duration="100"/>
   <frame tileid="2" duration="100"/>
   <frame tileid="3" duration="100"/>
   <frame tileid="4" duration="100"/>
   <frame tileid="5" duration="100"/>
   <frame tileid="6" duration="100"/>
   <frame tileid="7" duration="100"/>
   <frame tileid="8" duration="100"/>
   <frame tileid="9" duration="100"/>
   <frame tileid="10" duration="100"/>
   <frame tileid="11" duration="100"/>
  </animation>
 </tile>
 <tile id="11" type="ACTOR_TEMPLATE">
  <properties>
   <property name="ACTOR_NAME" value="Arrow"/>
   <property name="ANIMATION_TYPE" value="IDLE"/>
   <property name="base_force" type="float" value="1000"/>
   <property name="type" value="Arrow"/>
  </properties>
 </tile>
</tileset>
