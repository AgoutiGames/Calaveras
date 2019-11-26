<?xml version="1.0" encoding="UTF-8"?>
<tileset name="frog" tilewidth="64" tileheight="64" tilecount="48" columns="12">
 <image source="frog2.png" width="768" height="256"/>
 <tile id="0" type="ACTOR_ANIMATION">
  <properties>
   <property name="ACTOR_NAME" value="Frog"/>
   <property name="ANIMATION_TYPE" value="DIE"/>
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
 <tile id="12" type="ACTOR_ANIMATION">
  <properties>
   <property name="ACTOR_NAME" value="Frog"/>
   <property name="ANIMATION_TYPE" value="IDLE"/>
   <property name="DIRECTION" value="NONE"/>
  </properties>
  <animation>
   <frame tileid="12" duration="100"/>
   <frame tileid="13" duration="100"/>
   <frame tileid="14" duration="100"/>
   <frame tileid="15" duration="100"/>
   <frame tileid="16" duration="100"/>
   <frame tileid="17" duration="100"/>
   <frame tileid="18" duration="100"/>
   <frame tileid="19" duration="100"/>
   <frame tileid="20" duration="100"/>
   <frame tileid="21" duration="100"/>
   <frame tileid="22" duration="100"/>
   <frame tileid="23" duration="100"/>
  </animation>
 </tile>
 <tile id="17" type="ACTOR_TEMPLATE">
  <properties>
   <property name="ACTOR_NAME" value="Frog"/>
   <property name="ANIMATION_TYPE" value="IDLE"/>
   <property name="death_sound" type="file" value="../../sound/Hurt.wav"/>
   <property name="gravity" type="float" value="2000"/>
   <property name="jump_sound" type="file" value="../../sound/Jump.wav"/>
   <property name="type" value="Frog"/>
  </properties>
  <objectgroup draworder="index">
   <object id="1" x="19" y="24" width="26" height="38"/>
  </objectgroup>
 </tile>
 <tile id="36" type="ACTOR_ANIMATION">
  <properties>
   <property name="ACTOR_NAME" value="Frog"/>
   <property name="ANIMATION_TYPE" value="JUMP"/>
   <property name="DIRECTION" value="NONE"/>
  </properties>
  <animation>
   <frame tileid="36" duration="60"/>
   <frame tileid="37" duration="60"/>
   <frame tileid="38" duration="40"/>
   <frame tileid="39" duration="20"/>
   <frame tileid="40" duration="10"/>
   <frame tileid="41" duration="10"/>
   <frame tileid="42" duration="10"/>
   <frame tileid="43" duration="30"/>
   <frame tileid="44" duration="60"/>
   <frame tileid="45" duration="60"/>
   <frame tileid="46" duration="60"/>
   <frame tileid="47" duration="60"/>
   <frame tileid="24" duration="60"/>
   <frame tileid="25" duration="60"/>
   <frame tileid="26" duration="60"/>
   <frame tileid="27" duration="60"/>
   <frame tileid="28" duration="60"/>
   <frame tileid="29" duration="60"/>
   <frame tileid="30" duration="60"/>
   <frame tileid="31" duration="60"/>
   <frame tileid="32" duration="60"/>
   <frame tileid="33" duration="60"/>
   <frame tileid="34" duration="60"/>
   <frame tileid="35" duration="60"/>
  </animation>
 </tile>
</tileset>
