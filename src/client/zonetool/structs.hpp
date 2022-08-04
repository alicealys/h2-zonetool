#pragma once
#include <d3d11.h>

namespace zonetool
{
	typedef float vec_t;
	typedef vec_t vec2_t[2];
	typedef vec_t vec3_t[3];
	typedef vec_t vec4_t[4];

	template <std::size_t N>
	struct VecInternal
	{
		float data[N];
	};

	struct dummy
	{
	};

	enum scr_string_t : std::int32_t
	{
	};

	enum XAssetType
	{
		ASSET_TYPE_PHYSPRESET,
		ASSET_TYPE_PHYSCOLLMAP,
		ASSET_TYPE_PHYSWATERPRESET,
		ASSET_TYPE_PHYSWORLDMAP,
		ASSET_TYPE_PHYSCONSTRAINT,
		ASSET_TYPE_XANIM,
		ASSET_TYPE_XMODEL_SURFS,
		ASSET_TYPE_XMODEL,
		ASSET_TYPE_MATERIAL,
		ASSET_TYPE_COMPUTESHADER,
		ASSET_TYPE_VERTEXSHADER,
		ASSET_TYPE_HULLSHADER,
		ASSET_TYPE_DOMAINSHADER,
		ASSET_TYPE_PIXELSHADER,
		ASSET_TYPE_VERTEXDECL,
		ASSET_TYPE_TECHNIQUE_SET,
		ASSET_TYPE_IMAGE,
		ASSET_TYPE_SOUND,
		ASSET_TYPE_SOUNDSUBMIX,
		ASSET_TYPE_SOUND_CURVE,
		ASSET_TYPE_LPF_CURVE,
		ASSET_TYPE_REVERB_CURVE,
		ASSET_TYPE_SOUND_CONTEXT,
		ASSET_TYPE_LOADED_SOUND,
		ASSET_TYPE_COL_MAP_MP,
		ASSET_TYPE_COM_MAP,
		ASSET_TYPE_GLASS_MAP,
		ASSET_TYPE_AIPATHS,
		ASSET_TYPE_VEHICLE_TRACK,
		ASSET_TYPE_MAP_ENTS,
		ASSET_TYPE_FX_MAP,
		ASSET_TYPE_GFX_MAP,
		ASSET_TYPE_LIGHT_DEF,
		ASSET_TYPE_UI_MAP,
		ASSET_TYPE_MENUFILE,
		ASSET_TYPE_MENU,
		ASSET_TYPE_ANIMCLASS,
		ASSET_TYPE_LOCALIZE_ENTRY,
		ASSET_TYPE_ATTACHMENT,
		ASSET_TYPE_WEAPON,
		ASSET_TYPE_SNDDRIVERGLOBALS,
		ASSET_TYPE_FX,
		ASSET_TYPE_IMPACT_FX,
		ASSET_TYPE_SURFACE_FX,
		ASSET_TYPE_AITYPE,
		ASSET_TYPE_MPTYPE,
		ASSET_TYPE_CHARACTER,
		ASSET_TYPE_XMODELALIAS,
		ASSET_TYPE_RAWFILE,
		ASSET_TYPE_SCRIPTFILE,
		ASSET_TYPE_STRINGTABLE,
		ASSET_TYPE_LEADERBOARDDEF,
		ASSET_TYPE_VIRTUAL_LEADERBOARD,
		ASSET_TYPE_STRUCTUREDDATADEF,
		ASSET_TYPE_DDL,
		ASSET_TYPE_PROTO,
		ASSET_TYPE_TRACER,
		ASSET_TYPE_VEHICLE,
		ASSET_TYPE_ADDON_MAP_ENTS,
		ASSET_TYPE_NET_CONST_STRINGS,
		ASSET_TYPE_REVERB_PRESET,
		ASSET_TYPE_LUA_FILE,
		ASSET_TYPE_SCRIPTABLE,
		ASSET_TYPE_EQUIPMENT_SND_TABLE,
		ASSET_TYPE_VECTORFIELD,
		ASSET_TYPE_DOPPLER_PRESET,
		ASSET_TYPE_PARTICLE_SIM_ANIMATION,
		ASSET_TYPE_LASER,
		ASSET_TYPE_SKELETONSCRIPT,
		ASSET_TYPE_CLUT,
		ASSET_TYPE_TTF,
		ASSET_TYPE_COUNT
	};

	struct FxEffectDef;

	struct Bounds
	{
		vec3_t midPoint;
		vec3_t halfSize;
	};

	struct PhysPreset
	{
		const char* name;
		char __pad0[32];
		const char* sndAliasPrefix;
		char __pad1[48];
	}; static_assert(sizeof(PhysPreset) == 0x60);

	struct dmMeshNode_array_t
	{
		char __pad0[16];
	};

	struct dmMeshTriangle
	{
		char __pad0[32];
	};

	struct dmMeshData
	{
		dmMeshNode_array_t* meshNodes;
		vec4_t* vec4_array0;
		dmMeshTriangle* meshTriangles;
		char __pad0[36];
		unsigned int count0;
		unsigned int count1;
		unsigned int count2;
		char __pad1[8];
	}; static_assert(sizeof(dmMeshData) == 0x50);

	struct dmSubEdge
	{
		int value;
	};

	struct dmPolytopeData
	{
		vec4_t* vec4_array0;
		vec4_t* vec4_array1;
		unsigned short* uint16_array0;
		unsigned short* uint16_array1;
		dmSubEdge* edges;
		unsigned char* uint8_array0;
		char __pad0[12];
		unsigned int count0;
		unsigned int count1;
		unsigned int count2;
		char __pad1[40];
	}; static_assert(sizeof(dmPolytopeData) == 0x70);

	struct PhysGeomInfo
	{
		dmPolytopeData* data;
	};

	struct PhysMass
	{
		float centerOfMass[3];
		float momentsOfInertia[3];
		float productsOfInertia[3];
	};

	struct PhysCollmap
	{
		const char* name;
		unsigned int count;
		PhysGeomInfo* geoms;
		PhysMass mass;
		Bounds bounds;
	}; static_assert(sizeof(PhysCollmap) == 0x58);

	struct PhysWaterPreset
	{
		const char* name;
		char __pad0[64];
		FxEffectDef* fx0;
		FxEffectDef* fx1;
		FxEffectDef* fx2;
		FxEffectDef* fx3;
		FxEffectDef* fx4;
		FxEffectDef* fx5;
		FxEffectDef* fx6;
	}; static_assert(sizeof(PhysWaterPreset) == 0x80);

	struct PhysWaterVolumeDef
	{
		PhysWaterPreset* physWaterPreset;
		char __pad0[12];
		scr_string_t string;
		char __pad1[8];
	}; static_assert(sizeof(PhysWaterVolumeDef) == 0x20);
	static_assert(offsetof(PhysWaterVolumeDef, string) == 20);

	struct PhysBrushModel
	{
		char __pad0[8];
	};

	struct PhysWorld
	{
		const char* name;
		PhysBrushModel* models;
		dmPolytopeData* polytopeDatas;
		dmMeshData* meshDatas;
		PhysWaterVolumeDef* waterVolumes;
		unsigned int modelsCount;
		unsigned int polytopeDatasCount;
		unsigned int meshDatasCount;
		unsigned int waterVolumesCount;
	}; static_assert(sizeof(PhysWorld) == 0x38);

	struct PhysConstraint
	{
		const char* name;
		char __pad0[32];
	}; static_assert(sizeof(PhysConstraint) == 0x28);

	struct Packed128
	{
		std::uint64_t p0;
		std::uint64_t p1;
	};

	union GfxDrawSurf
	{
		//GfxDrawSurfFields fields;
		Packed128 packed;
	};

	struct GfxComputeShaderLoadDef
	{
		unsigned char* program;
		unsigned int programSize;
		char __pad[4];
	};

	struct ComputeShaderProgram
	{
		ID3D11ComputeShader* cs;
		GfxComputeShaderLoadDef loadDef;
	};

	struct ComputeShader
	{
		const char* name;
		ComputeShaderProgram prog;
	}; static_assert(sizeof(ComputeShader) == 0x20);

	struct GfxVertexShaderLoadDef
	{
		unsigned char* program;
		unsigned int programSize;
		unsigned int microCodeCrc;
	};

	struct MaterialVertexShaderProgram
	{
		ID3D11VertexShader* vs;
		GfxVertexShaderLoadDef loadDef;
	};

	struct MaterialVertexShader
	{
		const char* name;
		MaterialVertexShaderProgram prog;
	}; static_assert(sizeof(MaterialVertexShader) == 0x20);

	struct GfxPixelShaderLoadDef
	{
		unsigned char* program;
		unsigned int programSize;
		unsigned int microCodeCrc;
	};

	struct MaterialPixelShaderProgram
	{
		ID3D11PixelShader* ps;
		GfxPixelShaderLoadDef loadDef;
	};

	struct MaterialPixelShader
	{
		const char* name;
		MaterialPixelShaderProgram prog;
	}; static_assert(sizeof(MaterialPixelShader) == 0x20);

	struct GfxHullShaderLoadDef
	{
		unsigned char* program;
		unsigned int programSize;
		char __pad[4];
	};

	struct MaterialHullShaderProgram
	{
		ID3D11HullShader* hs;
		GfxHullShaderLoadDef loadDef;
	};

	struct MaterialHullShader
	{
		const char* name;
		MaterialHullShaderProgram prog;
	}; static_assert(sizeof(MaterialHullShader) == 0x20);

	struct GfxDomainShaderLoadDef
	{
		unsigned char* program;
		unsigned int programSize;
		char __pad[4];
	};

	struct MaterialDomainShaderProgram
	{
		ID3D11DomainShader* ds;
		GfxDomainShaderLoadDef loadDef;
	};

	struct MaterialDomainShader
	{
		const char* name;
		MaterialDomainShaderProgram prog;
	}; static_assert(sizeof(MaterialDomainShader) == 0x20);

	struct MaterialArgumentCodeConst
	{
		unsigned short index;
		unsigned char firstRow;
		unsigned char rowCount;
	};

	union MaterialArgumentDef
	{
		const float* literalConst;
		MaterialArgumentCodeConst codeConst;
		unsigned int codeSampler;
		unsigned int nameHash;
	};

	struct MaterialShaderArgument
	{
		unsigned char type;
		unsigned char shader;
		unsigned short dest;
		MaterialArgumentDef u;
	}; static_assert(sizeof(MaterialShaderArgument) == 0x10);

	struct MaterialStreamRouting
	{
		unsigned char source;
		unsigned char dest;
		unsigned char mask;
	};

	struct MaterialVertexStreamRouting
	{
		MaterialStreamRouting data[32];
		ID3D11InputLayout* decl[250];
	};

	struct MaterialVertexDeclaration
	{
		const char* name;
		unsigned char streamCount;
		bool hasOptionalSource;
		MaterialVertexStreamRouting routing;
	}; static_assert(sizeof(MaterialVertexDeclaration) == 0x840);

	struct MaterialPass
	{
		MaterialVertexShader* vertexShader;
		MaterialVertexDeclaration* vertexDecl;
		MaterialHullShader* hullShader;
		MaterialDomainShader* domainShader;
		MaterialPixelShader* pixelShader;
		unsigned char pixelOutputMask;
		unsigned char perPrimArgCount;
		unsigned char perObjArgCount;
		unsigned char stableArgCount;
		unsigned short perPrimArgSize;
		unsigned short perObjArgSize;
		unsigned short stableArgSize;
		unsigned short zone;
		unsigned char perPrimConstantBuffer;
		unsigned char perObjConstantBuffer;
		unsigned char stableConstantBuffer;
		unsigned int customBufferFlags;
		unsigned char customSamplerFlags;
		unsigned char precompiledIndex;
		unsigned char stageConfig;
		MaterialShaderArgument* args;
	};

	struct MaterialTechniqueHeader
	{
		const char* name;
		unsigned short flags;
		unsigned short passCount;
	};

	struct MaterialTechnique
	{
		//const char* name;
		//unsigned short flags;
		//unsigned short passCount;
		MaterialTechniqueHeader hdr;
		MaterialPass passArray[1];
	};

	struct MaterialTechniqueSet
	{
		const char* name;
		unsigned short flags;
		unsigned char worldVertFormat;
		unsigned char preDisplacementOnlyCount;
		MaterialTechnique* techniques[240];
	}; static_assert(sizeof(MaterialTechniqueSet) == 0x790);

	struct GfxImage;

	struct WaterWritable
	{
		float floatTime;
	};

	struct water_t
	{
		WaterWritable writable;
		float* H0X;
		float* H0Y;
		float* wTerm;
		int M;
		int N;
		float Lx;
		float Lz;
		float gravity;
		float windvel;
		float winddir[2];
		float amplitude;
		GfxImage* image;
		GfxImage* stagingImage;
	};

	union MaterialTextureDefInfo
	{
		GfxImage* image;
		water_t* water;
	};

	struct MaterialTextureDef
	{
		unsigned int nameHash;
		char nameStart;
		char nameEnd;
		unsigned char samplerState;
		unsigned char semantic;
		MaterialTextureDefInfo u;
	}; static_assert(sizeof(MaterialTextureDef) == 0x10);

	struct MaterialConstantDef
	{
		unsigned int nameHash;
		char name[12];
		float literal[4];
	}; static_assert(sizeof(MaterialConstantDef) == 0x20);

	struct GfxStateBits
	{
		unsigned int loadBits[6]; // loadbits[3], blendstatebits[3]
		unsigned short zone;
		unsigned char depthStencilState[11];
		unsigned char blendState;
		unsigned char rasterizerState;
	}; static_assert(sizeof(GfxStateBits) == 0x28);

	struct MaterialConstantBufferDef
	{
		unsigned int vsDataSize;
		unsigned int hsDataSize;
		unsigned int dsDataSize;
		unsigned int psDataSize;
		unsigned int vsOffsetDataSize;
		unsigned int hsOffsetDataSize;
		unsigned int dsOffsetDataSize;
		unsigned int psOffsetDataSize;
		unsigned char* vsData;
		unsigned char* hsData;
		unsigned char* dsData;
		unsigned char* psData;
		unsigned short* vsOffsetData;
		unsigned short* hsOffsetData;
		unsigned short* dsOffsetData;
		unsigned short* psOffsetData;
		ID3D11Buffer* vsConstantBuffer;
		ID3D11Buffer* hsConstantBuffer;
		ID3D11Buffer* dsConstantBuffer;
		ID3D11Buffer* psConstantBuffer;
	};

	struct MaterialInfo
	{
		const char* name;
		unsigned char gameFlags;
		unsigned char sortKey;
		unsigned char textureAtlasRowCount;
		unsigned char textureAtlasColumnCount;
		unsigned char textureAtlasFrameBlend;
		unsigned char textureAtlasAsArray;
		unsigned char renderFlags;
		GfxDrawSurf drawSurf;
		unsigned int surfaceTypeBits;
		unsigned short hashIndex;
		char __pad0[10];
	}; static_assert(sizeof(MaterialInfo) == 48);

	struct Material
	{
		union
		{
			const char* name;
			MaterialInfo info;
		};
		unsigned char stateBitsEntry[240];
		unsigned char textureCount;
		unsigned char constantCount;
		unsigned char stateBitsCount;
		unsigned char stateFlags;
		unsigned char cameraRegion;
		unsigned char materialType;
		unsigned char layerCount;
		unsigned char assetFlags;
		MaterialTechniqueSet* techniqueSet;
		MaterialTextureDef* textureTable;
		MaterialConstantDef* constantTable;
		GfxStateBits* stateBitsTable;
		unsigned char constantBufferIndex[240];
		MaterialConstantBufferDef* constantBufferTable;
		unsigned char constantBufferCount;
		const char** subMaterials;
	}; static_assert(sizeof(Material) == 0x250);

	struct GfxImageLoadDef
	{
		char levelCount;
		char numElements;
		char pad[2];
		int flags;
		int format;
		int resourceSize;
		char data[1];
	};

	struct GfxTexture
	{
		union
		{
			ID3D11Texture1D* linemap;
			ID3D11Texture2D* map;
			ID3D11Texture3D* volmap;
			ID3D11Texture2D* cubemap;
			GfxImageLoadDef* loadDef;
		};
		ID3D11ShaderResourceView* shaderView;
		ID3D11ShaderResourceView* shaderViewAlternate;
	};

	struct Picmip
	{
		unsigned char platform[2];
	};

	struct GfxImageStreamData
	{
		unsigned short width;
		unsigned short height;
		unsigned int pixelSize;
	};

	enum MapType : std::uint8_t
	{
		MAPTYPE_NONE = 0x0,
		MAPTYPE_INVALID1 = 0x1,
		MAPTYPE_1D = 0x2,
		MAPTYPE_2D = 0x3,
		MAPTYPE_3D = 0x4,
		MAPTYPE_CUBE = 0x5,
		MAPTYPE_ARRAY = 0x6,
		MAPTYPE_COUNT = 0x7,
	};

	struct GfxImage
	{
		GfxTexture texture;
		DXGI_FORMAT imageFormat;
		MapType mapType;
		unsigned char sematic;
		unsigned char category;
		unsigned char flags;
		Picmip picmip;
		char __pad0[2];
		unsigned int dataLen1;
		unsigned int dataLen2;
		unsigned short width;
		unsigned short height;
		unsigned short depth;
		unsigned short numElements;
		unsigned char levelCount;
		unsigned char streamed;
		char __pad1[2];
		unsigned char* pixelData;
		GfxImageStreamData streams[4];
		const char* name;
	}; static_assert(sizeof(GfxImage) == 0x68);

	struct GfxLightImage
	{
		GfxImage* image;
		unsigned char samplerState;
	};

	struct GfxLightDef
	{
		const char* name;
		GfxLightImage attenuation;
		GfxLightImage cucoloris;
		int lmapLookupStart;
	}; static_assert(sizeof(GfxLightDef) == 0x30);

	struct GfxColorFloat
	{
		float array[4];
	};

	enum snd_alias_type_t : std::int8_t
	{
		SAT_UNKNOWN = 0x0,
		SAT_LOADED = 0x1,
		SAT_STREAMED = 0x2,
		SAT_PRIMED = 0x3,
		SAT_COUNT = 0x4,
	};

	struct StreamFileNameRaw
	{
		const char* dir;
		const char* name;
	};

	struct StreamFileNamePacked
	{
		unsigned __int64 offset;
		unsigned __int64 length;
	};

	union StreamFileInfo
	{
		StreamFileNameRaw raw;
		StreamFileNamePacked packed;
	};

	struct StreamFileName
	{
		bool isLocalized;
		bool isStreamed;
		unsigned short fileIndex;
		StreamFileInfo info;
	};

	struct StreamedSound
	{
		StreamFileName filename;
		unsigned int totalMsec;
	};

	struct LoadedSoundInfo
	{
		char* data;
		unsigned int sampleRate;
		unsigned int dataByteCount;
		unsigned int numSamples;
		char channels;
		char numBits;
		char blockAlign;
		short format;
		int loadedSize;
	}; static_assert(sizeof(LoadedSoundInfo) == 0x20);

	struct LoadedSound
	{
		const char* name;
		StreamFileName filename;
		LoadedSoundInfo info;
	}; static_assert(sizeof(LoadedSound) == 0x40);

	struct PrimedSound
	{
		LoadedSound* loadedPart;
		StreamFileName streamedPart;
		int dataOffset; // not sure
		int totalSize; // not sure
	}; static_assert(sizeof(PrimedSound) == 0x28);

	union SoundFileRef
	{
		LoadedSound* loadSnd;
		StreamedSound streamSnd;
		PrimedSound primedSnd;
	};

	struct SoundFile
	{
		snd_alias_type_t type;
		bool exists;
		SoundFileRef u;
	};

	struct SndContext
	{
		const char* name;
		char __pad0[8];
	};

	struct SndCurve
	{
		bool isDefault;
		union
		{
			const char* filename;
			const char* name;
		};
		unsigned short knotCount;
		float knots[16][2];
	}; static_assert(sizeof(SndCurve) == 0x98);

	struct SpeakerLevels
	{
		char speaker;
		char numLevels;
		float levels[2];
	};

	struct ChannelMap
	{
		int speakerCount;
		SpeakerLevels speakers[6];
	};

	struct SpeakerMap
	{
		bool isDefault;
		const char* name;
		int unknown;
		ChannelMap channelMaps[2][2];
	}; static_assert(sizeof(SpeakerMap) == 0x148);

	struct DopplerPreset
	{
		const char* name;
		float speedOfSound;
		float playerVelocityScale;
		float minPitch;
		float maxPitch;
		float smoothing;
	}; static_assert(sizeof(DopplerPreset) == 0x20);

	struct snd_alias_t
	{
		const char* aliasName;
		const char* subtitle;
		const char* secondaryAliasName; 
		const char* chainAliasName;
		SoundFile* soundFile;
		const char* mixerGroup;
		short poly;
		short polyGlobal;
		char polyEntityType;
		char polyGlobalType;
		char dspBusIndex;
		char priority;
		char __pad0[12]; // unknown
		float volMin;
		float volMax;
		short volModIndex;
		//char __pad[1]; // padding
		float pitchMin;
		float pitchMax;
		float distMin;
		float distMax;
		float velocityMin;
		int flags;
		char masterPriority;
		float masterPercentage;
		float slavePercentage;
		char playbackPercentage;
		//char __pad[3]; // padding
		float probability;
		char u1; // value: 0-4
		//char __pad[3]; // padding
		SndContext* sndContext;
		unsigned char sequence;
		//char __pad[3]; // padding
		float lfePercentage;
		float centerPercentage;
		int startDelay;
		SndCurve* sndCurve;
		char __pad1[8]; // unknown
		SndCurve* lpfCurve;
		SndCurve* reverbSendCurve;
		SpeakerMap* speakerMap;
		float reverbWetMixOverride;
		char __pad2[4]; // unknown
		float smartPanDistance2d;
		float smartPanDistance3d;
		float smartPanAttenuation3d;
		char __pad3[4]; // unknown
		float stereo3dAngle;
		float stereo3dStart;
		float stereo3dEnd;
		unsigned char allowDoppler;
		DopplerPreset* dopplerPreset;
		char __pad4[8]; // unknown
	}; static_assert(sizeof(snd_alias_t) == 0xF8);
	static_assert(offsetof(snd_alias_t, soundFile) == 32);
	static_assert(offsetof(snd_alias_t, sndContext) == 128);
	static_assert(offsetof(snd_alias_t, sndCurve) == 152);
	static_assert(offsetof(snd_alias_t, lpfCurve) == 168);
	static_assert(offsetof(snd_alias_t, reverbSendCurve) == 176);
	static_assert(offsetof(snd_alias_t, speakerMap) == 184);
	static_assert(offsetof(snd_alias_t, dopplerPreset) == 232);

	struct snd_alias_list_t
	{
		union
		{
			const char* aliasName;
			const char* name;
		};
		snd_alias_t* head;
		short* unk;
		unsigned char count;
		unsigned char unkCount;
	}; static_assert(sizeof(snd_alias_list_t) == 0x20);

	struct LocalizeEntry
	{
		const char* value;
		const char* name;
	}; static_assert(sizeof(LocalizeEntry) == 0x10);

	struct TriggerModel
	{
		int contents;
		unsigned short hullCount;
		unsigned short firstHull;
	};

	struct TriggerHull
	{
		Bounds bounds;
		int contents;
		unsigned short slabCount;
		unsigned short firstSlab;
	};

	struct TriggerSlab
	{
		float dir[3];
		float midPoint;
		float halfSize;
	};

	struct MapTriggers
	{
		unsigned int count;
		TriggerModel* models;
		unsigned int hullCount;
		TriggerHull* hulls;
		unsigned int slabCount;
		TriggerSlab* slabs;
	};

	struct ClientTriggerAabbNode
	{
		Bounds bounds;
		unsigned short firstChild;
		unsigned short childCount;
	};

	struct ClientTriggers
	{
		MapTriggers trigger;
		unsigned short numClientTriggerNodes;
		ClientTriggerAabbNode* clientTriggerAabbTree;
		unsigned int triggerStringLength;
		char* triggerString;
		short* unk0;
		short* unk1;
		short* unk2;
		short* triggerType;
		vec3_t* origins;
		float* scriptDelay;
		short* unk3;
		short* unk4;
		short* unk5;
		short* unk6;
		short* unk7;
		short* unk8;
	}; static_assert(sizeof(ClientTriggers) == 0xB0);

	struct ClientTriggerBlendNode
	{
		float pointA[3];
		float pointB[3];
		unsigned short triggerA;
		unsigned short triggerB;
	};

	struct ClientTriggerBlend
	{
		unsigned short numClientTriggerBlendNodes;
		ClientTriggerBlendNode* blendNodes;
	};

	struct SpawnPointEntityRecord
	{
		unsigned short index;
		scr_string_t name;
		scr_string_t target;
		scr_string_t script_noteworthy;
		scr_string_t unknown;
		float origin[3];
		float angles[3];
	};

	struct SpawnPointRecordList
	{
		unsigned short spawnsCount;
		SpawnPointEntityRecord* spawns;
	};

	struct SplinePointEntityRecord
	{
		int splineId;
		int splineNodeId;
		char* splineNodeLabel;
		float splineNodeTension;
		float origin[3];
		float corridorDims[2];
		float tangent[3];
		float distToNextNode;
		vec3_t* positionCubic;
		vec3_t* tangentQuadratic;
	};

	struct SplinePointRecordList
	{
		unsigned short splinePointCount;
		float splineLength;
		SplinePointEntityRecord* splinePoints;
	};

	struct SplineRecordList
	{
		unsigned short splineCount;
		SplinePointRecordList* splines;
	};

	struct MapEnts
	{
		const char* name;
		char* entityString;
		int numEntityChars;
		MapTriggers trigger;
		ClientTriggers clientTrigger;
		ClientTriggerBlend clientTriggerBlend;
		SpawnPointRecordList spawnList;
		SplineRecordList splineList;
	}; static_assert(sizeof(MapEnts) == 0x128);

	struct RawFile
	{
		const char* name;
		int compressedLen;
		int len;
		const char* buffer;
	}; static_assert(sizeof(RawFile) == 0x18);

	struct ScriptFile
	{
		const char* name;
		int compressedLen;
		int len;
		int bytecodeLen;
		const char* buffer;
		char* bytecode;
	}; static_assert(sizeof(ScriptFile) == 0x28);

	struct StringTableCell
	{
		const char* string;
		int hash;
	};

	struct StringTable
	{
		const char* name;
		int columnCount;
		int rowCount;
		StringTableCell* values;
	}; static_assert(sizeof(StringTable) == 0x18);

	struct StructuredDataEnumEntry
	{
		scr_string_t string;
		unsigned short index;
	};

	struct StructuredDataEnum
	{
		int entryCount;
		int reservedEntryCount;
		StructuredDataEnumEntry* entries;
	};

	enum StructuredDataTypeCategory
	{
		DATA_INT = 0x0,
		DATA_BYTE = 0x1,
		DATA_BOOL = 0x2,
		DATA_STRING = 0x3,
		DATA_ENUM = 0x4,
		DATA_STRUCT = 0x5,
		DATA_INDEXED_ARRAY = 0x6,
		DATA_ENUM_ARRAY = 0x7,
		DATA_FLOAT = 0x8,
		DATA_SHORT = 0x9,
		DATA_COUNT = 0xA,
	};

	union StructuredDataTypeUnion
	{
		unsigned int stringDataLength;
		int enumIndex;
		int structIndex;
		int indexedArrayIndex;
		int enumedArrayIndex;
		int index;
	};

	struct StructuredDataType
	{
		StructuredDataTypeCategory type;
		StructuredDataTypeUnion u;
	};

	enum StructuredDataValidationType
	{
		VALIDATION_NONE = 0x0,
	};

	struct StructuredDataStructProperty
	{
		scr_string_t name;
		StructuredDataType type;
		unsigned int offset;
		StructuredDataValidationType validation;
	};

	struct StructuredDataStruct
	{
		int propertyCount;
		StructuredDataStructProperty* properties;
		int size;
		unsigned int bitOffset;
	};

	struct StructuredDataIndexedArray
	{
		int arraySize;
		StructuredDataType elementType;
		unsigned int elementSize;
	};

	struct StructuredDataEnumedArray
	{
		int enumIndex;
		StructuredDataType elementType;
		unsigned int elementSize;
	};

	struct StructuredDataDef
	{
		int version;
		unsigned int formatChecksum;
		int enumCount;
		StructuredDataEnum* enums;
		int structCount;
		StructuredDataStruct* structs;
		int indexedArrayCount;
		StructuredDataIndexedArray* indexedArrays;
		int enumedArrayCount;
		StructuredDataEnumedArray* enumedArrays;
		StructuredDataType rootType;
		unsigned int size;
	}; static_assert(sizeof(StructuredDataDef) == 0x58);

	struct StructuredDataDefSet
	{
		const char* name;
		unsigned int defCount;
		StructuredDataDef* defs;
	}; static_assert(sizeof(StructuredDataDefSet) == 0x18);

	enum NetConstStringType
	{
	};

	enum NetConstStringSource
	{
	};

	struct NetConstStrings
	{
		const char* name;
		NetConstStringType stringType;
		NetConstStringSource sourceType;
		unsigned int entryCount;
		const char** stringList;
	}; static_assert(sizeof(NetConstStrings) == 0x20);

	struct LuaFile
	{
		const char* name;
		int len;
		char strippingType;
		const char* buffer;
	}; static_assert(sizeof(LuaFile) == 0x18);

	struct TTFDef
	{
		const char* name;
		int fileLen;
		const char* file;
		void* ftFace;
	}; static_assert(sizeof(TTFDef) == 0x20);

	struct FxParticleSimAnimationHeader
	{
		float playbackRate;
		float duration;
		unsigned int frameCount;
		float minX;
		float minY;
		float minZ;
		float boundsXDelta;
		float boundsYDelta;
		float boundsZDelta;
		float maxWidth;
		float maxHeight;
		unsigned int colorTableSize;
		unsigned int particleDataCount;
		bool evalVisStatePerParticle;
		bool sortParticlesAtRuntime;
	};

	struct FxParticleSimAnimationParticleData
	{
		unsigned short xNormalizedPos;
		unsigned short yNormalizedPos;
		unsigned short zNormalizedPos;
		unsigned short xNormalizedWidth;
		unsigned short yNormalizedHeight;
		unsigned short orientation;
		unsigned short lifetime;
		unsigned short particleID;
		unsigned short xNormalizedPosNextFrame;
		unsigned short yNormalizedPosNextFrame;
		unsigned short zNormalizedPosNextFrame;
		unsigned short xNormalizedWidthNextFrame;
		unsigned short yNormalizedHeightNextFrame;
		short orientationDelta;
		unsigned short colorTableIndex;
		unsigned short nextColorTableIndex;
	};

	struct FxParticleSimAnimationFrame
	{
		unsigned int particleDataOffset;
		unsigned int numActiveParticles;
	};

	struct FxParticleSimAnimation
	{
		const char* name;
		Material* material;
		FxParticleSimAnimationHeader header;
		FxParticleSimAnimationParticleData* particleData;
		FxParticleSimAnimationFrame* frames;
		GfxColorFloat* colorTable;
	};

	enum FxElemType : std::uint8_t
	{
		FX_ELEM_TYPE_SPRITE_BILLBOARD = 0,
		FX_ELEM_TYPE_SPRITE_ORIENTED = 1,
		FX_ELEM_TYPE_SPRITE_ROTATED = 2,
		FX_ELEM_TYPE_TAIL = 3,
		FX_ELEM_TYPE_LINE = 4,
		FX_ELEM_TYPE_TRAIL = 5,
		FX_ELEM_TYPE_FLARE = 6,
		FX_ELEM_TYPE_PARTICLE_SIM_ANIMATION = 7,
		FX_ELEM_TYPE_CLOUD = 8,
		FX_ELEM_TYPE_SPARK_CLOUD = 9,
		FX_ELEM_TYPE_SPARK_FOUNTAIN = 10,
		FX_ELEM_TYPE_MODEL = 11,
		FX_ELEM_TYPE_OMNI_LIGHT = 12,
		FX_ELEM_TYPE_SPOT_LIGHT = 13,
		FX_ELEM_TYPE_SOUND = 14,
		FX_ELEM_TYPE_DECAL = 15,
		FX_ELEM_TYPE_RUNNER = 16,
		FX_ELEM_TYPE_VECTORFIELD = 17,
	};

	struct FxFloatRange
	{
		float base;
		float amplitude;
	};

	struct FxSpawnDefLooping
	{
		int intervalMsec;
		int count;
	};

	struct FxIntRange
	{
		int base;
		int amplitude;
	};

	struct FxSpawnDefOneShot
	{
		FxIntRange count;
	};

	union FxSpawnDef
	{
		FxSpawnDefLooping looping;
		FxSpawnDefOneShot oneShot;
	};

	struct FxElemAtlas
	{
		unsigned char behavior;
		unsigned char index;
		unsigned char fps;
		unsigned char loopCount;
		unsigned char colIndexBits;
		unsigned char rowIndexBits;
		short entryCount;
	};

	struct FxEffectDef;
	union FxEffectDefRef
	{
		FxEffectDef* handle;
		const char* name;
	};

	struct FxElemVec3Range
	{
		float base[3];
		float amplitude[3];
	};

	struct FxElemVelStateInFrame
	{
		FxElemVec3Range velocity;
		FxElemVec3Range totalDelta;
	};

	struct FxElemVelStateSample
	{
		FxElemVelStateInFrame local;
		FxElemVelStateInFrame world;
	}; static_assert(sizeof(FxElemVelStateSample) == 96);

	struct FxElemVisualState
	{
		float color[4];
		float unlitHDRScale;
		float rotationDelta;
		float rotationTotal;
		float size[2];
		float scale;
		char __pad0[16];
	};

	struct FxElemVisStateSample
	{
		FxElemVisualState base;
		FxElemVisualState amplitude;
	}; static_assert(sizeof(FxElemVisStateSample) == 112);

	struct FxElemMarkVisuals
	{
		Material* materials[3];
	};

	struct XModel;
	union FxElemVisuals
	{
		const void* anonymous;
		Material* material;
		XModel* model;
		FxEffectDefRef effectDef;
		const char* soundName;
		const char* vectorFieldName;
		GfxLightDef* lightDef;
		FxParticleSimAnimation* particleSimAnimation;
	};

	union FxElemDefVisuals
	{
		FxElemMarkVisuals* markArray;
		FxElemVisuals* array;
		FxElemVisuals instance;
	};

	struct FxTrailVertex
	{
		float pos[2];
		float normal[2];
		float texCoord[2];
		char __pad0[8];
	}; static_assert(sizeof(FxTrailVertex) == 32);

	struct FxTrailDef
	{
		int scrollTimeMsec;
		int repeatDist;
		float invSplitDist;
		float invSplitArcDist;
		float invSplitTime;
		char __pad0[8];
		int vertCount;
		FxTrailVertex* verts;
		int indCount;
		unsigned short* inds;
	}; static_assert(sizeof(FxTrailDef) == 0x38);
	static_assert(offsetof(FxTrailDef, vertCount) == 28);

	struct FxSparkFountainDef
	{
		float gravity;
		float bounceFrac;
		float bounceRand;
		float sparkSpacing;
		float sparkLength;
		int sparkCount;
		float loopTime;
		float velMin;
		float velMax;
		float velConeFrac;
		float restSpeed;
		float boostTime;
		float boostFactor;
	}; static_assert(sizeof(FxSparkFountainDef) == 0x34);

	struct FxSpotLightDef
	{
		float fovInnerFraction;
		float startRadius;
		float endRadius;
		float brightness;
		float maxLength;
		int exponent;
		char __pad0[24];
	}; static_assert(sizeof(FxSpotLightDef) == 0x30);

	struct FxOmniLightDef
	{
		char __pad0[16];
	}; static_assert(sizeof(FxOmniLightDef) == 0x10);

	struct FxFlareDef
	{
		float position;
		int angularRotCount;
		int flags;
		FxFloatRange depthScaleRange;
		FxFloatRange depthScaleValue;
		FxFloatRange radialRot;
		FxFloatRange radialScaleX;
		FxFloatRange radialScaleY;
		float dir[3];
		int intensityXIntervalCount;
		int intensityYIntervalCount;
		int srcCosIntensityIntervalCount;
		int srcCosScaleIntervalCount;
		float* intensityX;
		float* intensityY;
		float* srcCosIntensity;
		float* srcCosScale;
	}; static_assert(sizeof(FxFlareDef) == 0x70);

	union FxElemExtendedDefPtr
	{
		char* unknownDef;
		FxTrailDef* trailDef;
		FxSparkFountainDef* sparkFountainDef;
		FxSpotLightDef* spotLightDef;
		FxOmniLightDef* omniLightDef;
		FxFlareDef* flareDef;
	};

	struct FxElemDef
	{
		int flags;
		int flags2;
		FxSpawnDef spawn;
		FxFloatRange spawnRange;
		FxFloatRange fadeInRange;
		FxFloatRange fadeOutRange;
		float spawnFrustumCullRadius;
		FxIntRange spawnDelayMsec;
		FxIntRange lifeSpanMsec;
		FxFloatRange spawnOrigin[3];
		FxFloatRange spawnOffsetRadius;
		FxFloatRange spawnOffsetHeight;
		FxFloatRange spawnAngles[3];
		FxFloatRange angularVelocity[3];
		FxFloatRange initialRotation;
		FxFloatRange gravity;
		FxFloatRange reflectionFactor;
		FxElemAtlas atlas;
		FxElemType elemType;
		unsigned char elemLitType;
		unsigned char visualCount;
		unsigned char velIntervalCount;
		unsigned char visStateIntervalCount;
		FxElemVelStateSample* velSamples;
		FxElemVisStateSample* visSamples;
		FxElemDefVisuals visuals;
		Bounds collBounds;
		FxEffectDefRef effectOnImpact;
		FxEffectDefRef effectOnDeath;
		FxEffectDefRef effectEmitted;
		FxFloatRange emitDist;
		FxFloatRange emitDistVariance;
		FxElemExtendedDefPtr extended;
		unsigned char sortOrder;
		unsigned char lightingFrac;
		unsigned char useItemClip;
		unsigned char fadeInfo;
		int randomSeed;
		char __pad0[24];
	}; static_assert(sizeof(FxElemDef) == 0x140);

	struct FxEffectDef
	{
		const char* name;
		int flags;
		int totalSize;
		int msecLoopingLife;
		int elemDefCountLooping;
		int elemDefCountOneShot;
		int elemDefCountEmission;
		float elemMaxRadius;
		float occlusionQueryDepthBias;
		int occlusionQueryFadeIn;
		int occlusionQueryFadeOut;
		FxFloatRange occlusionQueryScaleRange;
		FxElemDef* elemDefs;
	}; static_assert(sizeof(FxEffectDef) == 0x40);

	struct XModelIKData
	{
		unsigned char charDataLen;
		unsigned char floatDataLen;
		unsigned char int32DataLen;
		unsigned char stringsCount;
		char* charData;
		float* floatData;
		int* int32Data;
		scr_string_t* strings;
	}; static_assert(sizeof(XModelIKData) == 0x28);

	struct SkeletonScriptCode
	{
		char __pad0[4];
	};

	struct SkeletonScript
	{
		const char* name;
		XModelIKData* ikData;
		char __pad0[32];
		unsigned short codeLen;
		char __pad1[6];
		SkeletonScriptCode* code;
	}; static_assert(sizeof(SkeletonScript) == 0x40);

	union XAnimDynamicFrames
	{
		unsigned char(*_1)[3];
		unsigned short(*_2)[3];
	};

	union XAnimDynamicIndices
	{
		unsigned char _1[1];
		unsigned short _2[1];
	};

	struct XAnimPartTransFrames
	{
		float mins[3];
		float size[3];
		XAnimDynamicFrames frames;
		XAnimDynamicIndices indices;
	};

	union XAnimPartTransData
	{
		XAnimPartTransFrames frames;
		float frame0[3];
	};

	struct XAnimPartTrans
	{
		unsigned short size;
		unsigned char smallTrans;
		XAnimPartTransData u;
	};

	struct XAnimDeltaPartQuatDataFrames2
	{
		short(*frames)[2];
		XAnimDynamicIndices indices;
	};

	union XAnimDeltaPartQuatData2
	{
		XAnimDeltaPartQuatDataFrames2 frames;
		short frame0[2];
	};

	struct XAnimDeltaPartQuat2
	{
		unsigned short size;
		XAnimDeltaPartQuatData2 u;
	};

	struct XAnimDeltaPartQuatDataFrames
	{
		short(*frames)[4];
		XAnimDynamicIndices indices;
	};

	union XAnimDeltaPartQuatData
	{
		XAnimDeltaPartQuatDataFrames frames;
		short frame0[4];
	};

	struct XAnimDeltaPartQuat
	{
		unsigned short size;
		XAnimDeltaPartQuatData u;
	};

	struct XAnimDeltaPart
	{
		XAnimPartTrans* trans;
		XAnimDeltaPartQuat2* quat2;
		XAnimDeltaPartQuat* quat;
	};

	union XAnimIndices
	{
		unsigned char* _1;
		unsigned short* _2;
		void* data;
	};

	struct XAnimNotifyInfo
	{
		scr_string_t name;
		float time;
	};

	enum XAnimPartsFlags : std::uint8_t
	{
		ANIM_NONE = 0x0,
		ANIM_LOOP = 0x1,
		ANIM_DELTA = 0x2,
		ANIM_DELTA_3D = 0x4,
		ANIM_DEFAULT = 0x8,
	};

	typedef float BlendShapeWeight;
	typedef char XAnimScriptedViewmodelAnimData;

	struct XAnimParts
	{
		const char* name; // 0
		unsigned short dataByteCount; // 8
		unsigned short dataShortCount; // 10
		unsigned short dataIntCount; // 12
		unsigned short numframes; // 14
		unsigned char flags; // 15
		unsigned char boneCount[10]; // 16
		char u1; // unused?
		char u2; // unused?
		unsigned char notifyCount; // 29
		unsigned char assetType; // 30
		unsigned char ikType; // 31
		unsigned int randomDataByteCount; // 32
		unsigned int randomDataShortCount; // 36
		unsigned int randomDataIntCount; // 40
		unsigned int indexCount; // 44
		float framerate;  // 48
		float frequency; // 56
		scr_string_t* names; // 56
		char* dataByte; // 64
		short* dataShort; // 72
		int* dataInt; // 80
		short* randomDataShort; // 88
		unsigned char* randomDataByte; // 96
		int* randomDataInt; // 104
		XAnimIndices indices; // 112
		XAnimNotifyInfo* notify; // 120
		XAnimDeltaPart* deltaPart; // 128
		const char* secondaryName; // 136
		short u3; // unknown
		unsigned short blendShapeWeightCount; // 146
		short u4; // unused? padding?
		scr_string_t* blendShapeWeightNames; // 152
		char (*blendShapeWeightUnknown1)[3]; // 160
		unsigned short* blendShapeWeightUnknown2; // 168
		unsigned short* blendShapeWeightUnknown3; // 176
		unsigned short* blendShapeWeightUnknown4; // 184
		BlendShapeWeight* blendShapeWeights; // 192
		std::uint64_t u5; // unused?
		XAnimScriptedViewmodelAnimData* scriptedViewmodelAnimData; // 208 // count = 8
	}; static_assert(sizeof(XAnimParts) == 0xD8);

	union PackedUnitVec
	{
		unsigned int packed;
	};

	union PackedTexCoords
	{
		unsigned int packed;
	};

	union GfxColor
	{
		unsigned char array[4];
		unsigned int packed;
	};

	struct GfxPackedVertex
	{
		float xyz[3];
		float binormalSign;
		GfxColor color;
		PackedTexCoords texCoord;
		PackedUnitVec normal;
		PackedUnitVec tangent;
	};

	struct GfxPackedMotionVertex
	{
		float xyz[3];
		float binormalSignAndHeight;
		GfxColor pieceIndex;
		PackedTexCoords texCoord;
		PackedUnitVec normal;
		PackedUnitVec tangent;
	};

	union GfxVertexUnion0
	{
		GfxPackedVertex* packedVerts0;
		GfxPackedMotionVertex* packedMotionVerts0;
		void* verts0;
	};

	struct Face
	{
		unsigned short v1;
		unsigned short v2;
		unsigned short v3;
	};

	struct XSurfaceCollisionAabb
	{
		unsigned short mins[3];
		unsigned short maxs[3];
	};

	struct XSurfaceCollisionNode
	{
		XSurfaceCollisionAabb aabb;
		unsigned short childBeginIndex;
		unsigned short childCount;
	};

	struct XSurfaceCollisionLeaf
	{
		unsigned short triangleBeginIndex;
	};

	struct XSurfaceCollisionTree
	{
		float trans[3];
		float scale[3];
		unsigned int nodeCount;
		XSurfaceCollisionNode* nodes;
		unsigned int leafCount;
		XSurfaceCollisionLeaf* leafs;
	};

	struct XRigidVertList
	{
		unsigned short boneOffset;
		unsigned short vertCount;
		unsigned short triOffset;
		unsigned short triCount;
		XSurfaceCollisionTree* collisionTree;
	};

	struct UnknownXSurface0
	{
		float a[3];
		union
		{
			float b0;
			unsigned int b1;
		};
	};

	struct XSubdivRigidVertList
	{
		unsigned int firstFace;
		unsigned int faceCount;
		unsigned int firstRegularPatch;
		unsigned int regularPatchCount;
	};

	struct XSurfaceSubdivLevel
	{
		XSubdivRigidVertList* rigidVertLists;
		unsigned int faceCount;
		unsigned int regularPatchCount;
		unsigned int regularPatchOffset;
		unsigned int facePointCount;
		unsigned int facePointValence4Count;
		unsigned int facePointBufferSize;
		unsigned int edgePointCount;
		unsigned int edgePointSmoothEnd;
		unsigned int edgePointUVBorderEnd;
		unsigned int vertexPointCount;
		unsigned int vertexPointValence4Count;
		unsigned int vertexPointBufferSize;
		unsigned int normalCount;
		unsigned int normalBufferSize;
		unsigned int transitionPointCount;
		unsigned int vertCount;
		unsigned int vertOffset;
		unsigned short* faceIndices;
		unsigned short* regularPatchIndices;
		unsigned int* regularPatchFlags;
		unsigned int* facePoints;
		unsigned int* edgePoints;
		unsigned int* vertexPoints;
		unsigned int* normals;
		unsigned int* transitionPoints;
		float* regularPatchCones;
		ID3D11Buffer* regularPatchIndexBuffer;
		ID3D11Buffer* faceIndexBuffer;
		ID3D11ShaderResourceView* regularPatchIndexBufferView;
		ID3D11ShaderResourceView* regularPatchFlagsView;
		ID3D11ShaderResourceView* facePointsView;
		ID3D11ShaderResourceView* edgePointsView;
		ID3D11ShaderResourceView* vertexPointsView;
		ID3D11ShaderResourceView* normalsView;
		ID3D11ShaderResourceView* transitionPointsView;
		ID3D11ShaderResourceView* regularPatchConesView;
	}; static_assert(sizeof(XSurfaceSubdivLevel) == 0xE8);

	struct GfxSubdivCache
	{
		unsigned int size;
		ID3D11Buffer* subdivCacheBuffer;
		ID3D11ShaderResourceView* subdivCacheView;
	}; static_assert(sizeof(GfxSubdivCache) == 0x18);

	struct XSurfaceSubdivInfo
	{
		XSurfaceSubdivLevel* levels;
		char __pad0[24];
		GfxSubdivCache cache;
	}; static_assert(sizeof(XSurfaceSubdivInfo) == 0x38);

	struct BlendShapeVert
	{
		char __pad0[32];
	};

	struct BlendShape
	{
		unsigned int vertCount;
		BlendShapeVert* verts;
		ID3D11Buffer* blendShapeVertsBuffer;
		ID3D11ShaderResourceView* blendShapeVertsView;
	};

	typedef unsigned short XBlendInfo;

	struct XSurface
	{
		unsigned short flags;
		unsigned short vertCount;
		unsigned short triCount;
		unsigned char rigidVertListCount;
		unsigned char subdivLevelCount;
		short blendVertCounts[8];
		GfxVertexUnion0 verts0;
		Face* triIndices;
		Face* triIndices2;
		ID3D11Buffer* vb0;
		ID3D11ShaderResourceView* vb0View;
		ID3D11Buffer* indexBuffer;
		XRigidVertList* rigidVertLists;
		UnknownXSurface0* unknown0;
		XBlendInfo* blendVerts;
		unsigned short* blendVertsTable;
		ID3D11Buffer* blendVertsBuffer;
		ID3D11ShaderResourceView* blendVertsView;
		std::uint16_t(*lmapUnwrap)[2];
		ID3D11Buffer* vblmapBuffer;
		ID3D11ShaderResourceView* vblmapView;
		XSurfaceSubdivInfo* subdiv;
		float* tensionData;
		unsigned short* tensionAccumTable;
		ID3D11Buffer* tensionAccumTableBuffer;
		ID3D11ShaderResourceView* tensionAccumTableView;
		ID3D11Buffer* tensionDataBuffer;
		ID3D11ShaderResourceView* tensionDataView;
		ID3D11ShaderResourceView* indexBufferView;
		BlendShape* blendShapes;
		unsigned int blendShapesCount;
		unsigned int vertexLightingIndex;
		char __pad0[4];
		int partBits[8];
		char __pad1[4];
	}; static_assert(sizeof(XSurface) == 0x108);

	struct XModelSurfs
	{
		const char* name;
		XSurface* surfs;
		unsigned short numsurfs;
		int partBits[8];
	}; static_assert(sizeof(XModelSurfs) == 0x38);

	struct XModelLodInfo
	{
		float dist;
		unsigned short numsurfs;
		unsigned short surfIndex;
		XModelSurfs* modelSurfs;
		int partBits[8];
		XSurface* surfs;
		char unknown[8];
	};

	struct XModelAngle
	{
		short x;
		short y;
		short z;
		short base;
	};

	struct XModelTagPos
	{
		float x;
		float y;
		float z;
	};

	struct DObjAnimMat
	{
		float quat[4];
		float trans[3];
		float transWeight;
	};

	struct ReactiveMotionModelPart
	{
		float center[3];
		float stiffness;
	};

	struct ReactiveMotionModelTweaks
	{
		float scale[4];
	};

	struct XModelCollSurf_s
	{
		Bounds bounds;
		int boneIdx;
		int contents;
		int surfFlags;
	};

	struct XBoneInfo
	{
		Bounds bounds;
		union
		{
			float radiusSquared;
			unsigned int radiusSquaredAsInt;
		};
	};

	struct BlendShapeWeightMap
	{
		unsigned short weightIndex;
		unsigned short targetIndex;
		float fullWeight;
	};

	struct ExtentBounds
	{
		vec3_t mins;
		vec3_t maxs;
	};

	struct MdaoVolume
	{
		ExtentBounds bounds;
		unsigned __int16 cellCount[3];
		unsigned __int16 parentBoneIndex;
		GfxImage* volumeData;
	}; static_assert(sizeof(MdaoVolume) == 0x28);

	struct XPhysBoneInfo
	{
		PhysPreset* physPreset;
		PhysConstraint* physContraint;
		PhysCollmap* physCollmap;
		char __pad0[8];
	}; static_assert(sizeof(XPhysBoneInfo) == 0x20);

	enum XModelFlags : std::uint16_t
	{
		XMODEL_FLAG_COMPOSITE = 0x400,
	};

	struct XModel
	{
		const char* name; // 0
		unsigned char numBones; // 8
		unsigned char numRootBones; // 9
		unsigned char numsurfs; // 10
		unsigned char numReactiveMotionParts; // 11
		unsigned char lodRampType; // 12
		unsigned char numBonePhysics; // 13
		char __pad0[2]; // 14-16
		float scale; // 16
		unsigned int noScalePartBits[8]; // 20
		scr_string_t* boneNames; // 56
		unsigned char* parentList; // 64
		XModelAngle* tagAngles; // 72
		XModelTagPos* tagPositions; // 80
		unsigned char* partClassification; // 88
		DObjAnimMat* baseMat; // 96
		ReactiveMotionModelPart* reactiveMotionParts; // 104
		ReactiveMotionModelTweaks* reactiveMotionTweaks; // 112
		Material** materialHandles; // 120
		XModelLodInfo lodInfo[6]; // 128
		char numLods; // 512
		char collLod; // 513
		char numCompositeModels; // 514
		char u1; // 515
		short flags; // 516
		short numCollSurfs; // 518
		XModelCollSurf_s* collSurfs; // 520
		int contents; // 528
		XBoneInfo* boneInfo; // 536
		float radius; // 544
		Bounds bounds; // 548
		unsigned short* invHighMipRadius; // 576
		int memUsage; // 584
		bool bad; // 588
		char pad; // 589
		unsigned short targetCount; // 590
		unsigned short numberOfWeights; // 592
		unsigned short numberOfWeightMaps; // 594
		char __pad2[4]; // 596-600
		scr_string_t* weightNames; // 600
		BlendShapeWeightMap* blendShapeWeightMap; // 608
		PhysPreset* physPreset; // 616
		PhysCollmap* physCollmap; // 624
		unsigned short mdaoVolumeCount; // 632
		short u3; // 634
		float quantization; // 636
		MdaoVolume* mdaoVolumes; // 640
		int u4; // 648
		int u5; // 652
		SkeletonScript* skeletonScript; // 656
		XModel** compositeModels; // 664
		XPhysBoneInfo* bonePhysics; // 672
	}; static_assert(sizeof(XModel) == 0x2A8);

	union XAssetHeader
	{
		void* data;
		PhysPreset* physPreset;
		PhysCollmap* physCollmap;
		PhysWaterPreset* physWaterPreset;
		PhysWorld* physWorld;
		PhysConstraint* physConstraint;
		XAnimParts* parts;
		XModelSurfs* modelSurfs;
		XModel* model;
		Material* material;
		ComputeShader* computeShader;
		MaterialVertexShader* vertexShader;
		MaterialHullShader* hullShader;
		MaterialDomainShader* domainShader;
		MaterialPixelShader* pixelShader;
		MaterialVertexDeclaration* vertexDecl;
		MaterialTechniqueSet* techniqueSet;
		GfxImage* image;
		snd_alias_list_t* sound;
		SndCurve* sndCurve;
		SndCurve* lpfCurve;
		SndCurve* reverbCurve;
		SndContext* sndContext;
		LoadedSound* loadSnd;
		LocalizeEntry* localize;
		MapEnts* mapEnts;
		GfxLightDef* lightDef;
		FxEffectDef* fx;
		RawFile* rawfile;
		ScriptFile* scriptfile;
		StringTable* stringTable;
		StructuredDataDefSet* structuredDataDefSet;
		NetConstStrings* netConstStrings;
		LuaFile* luaFile;
		DopplerPreset* doppler;
		FxParticleSimAnimation* particleSimAnimation;
		SkeletonScript* skeletonScript;
		TTFDef* ttfDef;
	};

	struct XAsset
	{
		XAssetType type;
		XAssetHeader header;
	};

	struct XAssetEntry
	{
		XAsset asset;
		char zoneIndex;
		volatile char inuseMask;
		unsigned int nextHash;
		unsigned int nextOverride;
		unsigned int nextPoolEntry;
	};

	struct ScriptStringList
	{
		int count;
		const char** strings;
	};

	union GfxZoneTableEntry
	{
		char* dataPtr;
		void* voidPtr;
		ID3D11Buffer* buffer;
		ID3D11DepthStencilState* depthStencilState;
		ID3D11BlendState* blendState;
	};

	struct XGfxGlobals
	{
		unsigned int depthStencilStateCount;
		unsigned int blendStateCount;
		std::uint64_t* depthStencilStateBits;
		std::uint32_t (*blendStateBits)[3];
		GfxZoneTableEntry* depthStencilStates;
		GfxZoneTableEntry* blendStates;
		unsigned int perPrimConstantBufferCount;
		unsigned int perObjConstantBufferCount;
		unsigned int stableConstantBufferCount;
		unsigned int* perPrimConstantBufferSizes;
		unsigned int* perObjConstantBufferSizes;
		unsigned int* stableConstantBufferSizes;
		GfxZoneTableEntry* perPrimConstantBuffers;
		GfxZoneTableEntry* perObjConstantBuffers;
		GfxZoneTableEntry* stableConstantBuffers;
	};

	struct XGlobals
	{
		XGfxGlobals* gfxGlobals;
	};

	struct XAssetList
	{
		ScriptStringList stringList;
		int assetCount;
		XAsset* assets;
		XGlobals* globals;
	};

	enum DBSyncMode
	{
		DB_LOAD_ASYNC = 0x0,
		DB_LOAD_SYNC = 0x1,
		DB_LOAD_ASYNC_WAIT_ALLOC = 0x2,
		DB_LOAD_ASYNC_FORCE_FREE = 0x3,
		DB_LOAD_ASYNC_NO_SYNC_THREADS = 0x4,
		DB_LOAD_SYNC_SKIP_ALWAYS_LOADED = 0x5,
	};

	enum DBAllocFlags : std::int32_t
	{
		DB_ZONE_NONE = 0x0,
		DB_ZONE_COMMON = 0x1,
		DB_ZONE_UI = 0x2,
		DB_ZONE_GAME = 0x4,
		DB_ZONE_LOAD = 0x8,
		DB_ZONE_DEV = 0x10,
		DB_ZONE_BASEMAP = 0x20,
		DB_ZONE_TRANSIENT_POOL = 0x40,
		DB_ZONE_TRANSIENT_MASK = 0x40,
		DB_ZONE_CUSTOM = 0x400 // added for custom zone loading
	};

	struct XZoneInfo
	{
		const char* name;
		int allocFlags;
		int freeFlags;
	};

	struct XZoneInfoInternal
	{
		char name[64];
		int flags;
		int isBaseMap;
	};
}