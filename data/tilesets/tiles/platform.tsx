<?xml version="1.0" encoding="UTF-8"?>
<tileset name="platform" tilewidth="64" tileheight="64" tilecount="6" columns="3">
 <image source="platform.png" width="192" height="128"/>
 <terraintypes>
  <terrain name="Platform" tile="0"/>
 </terraintypes>
 <tile id="0" terrain=",,,0">
  <objectgroup draworder="index">
   <object id="1" x="11" y="20" width="53" height="44"/>
  </objectgroup>
 </tile>
 <tile id="1" terrain=",,0,0">
  <objectgroup draworder="index">
   <object id="1" x="0" y="20" width="64" height="44"/>
  </objectgroup>
 </tile>
 <tile id="2" terrain=",,0,">
  <objectgroup draworder="index">
   <object id="1" x="0" y="20" width="53" height="44"/>
  </objectgroup>
 </tile>
 <tile id="3" terrain=",0,,0">
  <objectgroup draworder="index">
   <object id="1" x="11" y="0" width="53" height="64"/>
  </objectgroup>
 </tile>
 <tile id="4" terrain="0,0,0,0">
  <objectgroup draworder="index">
   <object id="1" x="0" y="0" width="64" height="64"/>
  </objectgroup>
 </tile>
 <tile id="5" terrain="0,,0,">
  <objectgroup draworder="index">
   <object id="1" x="0" y="0" width="53" height="64"/>
  </objectgroup>
 </tile>
</tileset>
