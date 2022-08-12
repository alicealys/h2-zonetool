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
		unsigned char depthStencilState[10];
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

	enum SurfaceTypeBits : std::uint64_t
	{
		SURFTYPE_BITS_NONE = 0x0,
		SURFTYPE_BITS_DEFAULT = 0x1,
		SURFTYPE_BITS_BARK = 0x2,
		SURFTYPE_BITS_CARPET = 0x4,
		SURFTYPE_BITS_CLOTH = 0x8,
		SURFTYPE_BITS_CONCRETE = 0x10,
		SURFTYPE_BITS_DIRT = 0x20,
		SURFTYPE_BITS_FLESH = 0x40,
		SURFTYPE_BITS_FOLIAGE_DEBRIS = 0x80,
		SURFTYPE_BITS_GLASS = 0x100,
		SURFTYPE_BITS_GRASS = 0x200,
		SURFTYPE_BITS_GRAVEL = 0x400,
		SURFTYPE_BITS_ICE = 0x800,
		SURFTYPE_BITS_METAL_SOLID = 0x1000,
		SURFTYPE_BITS_METAL_GRATE = 0x2000,
		SURFTYPE_BITS_MUD = 0x4000,
		SURFTYPE_BITS_PAPER = 0x8000,
		SURFTYPE_BITS_PLASTER = 0x10000,
		SURFTYPE_BITS_ROCK = 0x20000,
		SURFTYPE_BITS_SAND = 0x40000,
		SURFTYPE_BITS_SNOW = 0x80000,
		SURFTYPE_BITS_WATER_WAIST = 0x100000,
		SURFTYPE_BITS_WOOD_SOLID = 0x200000,
		SURFTYPE_BITS_ASPHALT = 0x400000,
		SURFTYPE_BITS_CERAMIC = 0x800000,
		SURFTYPE_BITS_PLASTIC_SOLID = 0x1000000,
		SURFTYPE_BITS_RUBBER = 0x2000000,
		SURFTYPE_BITS_FRUIT = 0x4000000,
		SURFTYPE_BITS_PAINTEDMETAL = 0x8000000,
		SURFTYPE_BITS_RIOTSHIELD = 0x10000000,
		SURFTYPE_BITS_SLUSH = 0x20000000,
		SURFTYPE_BITS_ASPHALT_WET = 0x40000000,
		SURFTYPE_BITS_ASPHALT_DEBRIS = 0x80000000,
		SURFTYPE_BITS_CONCRETE_WET = 0x100000000,
		SURFTYPE_BITS_CONCRETE_DEBRIS = 0x200000000,
		SURFTYPE_BITS_FOLIAGE_VEGETATION = 0x400000000,
		SURFTYPE_BITS_FOLIAGE_LEAVES = 0x800000000,
		SURFTYPE_BITS_GRASS_TALL = 0x1000000000,
		SURFTYPE_BITS_METAL_HOLLOW = 0x2000000000,
		SURFTYPE_BITS_METAL_VEHICLE = 0x4000000000,
		SURFTYPE_BITS_METAL_THIN = 0x8000000000,
		SURFTYPE_BITS_METAL_WET = 0x10000000000,
		SURFTYPE_BITS_METAL_DEBRIS = 0x20000000000,
		SURFTYPE_BITS_PLASTIC_HOLLOW = 0x40000000000,
		SURFTYPE_BITS_PLASTIC_TARP = 0x80000000000,
		SURFTYPE_BITS_ROCK_WET = 0x100000000000,
		SURFTYPE_BITS_ROCK_DEBRIS = 0x200000000000,
		SURFTYPE_BITS_WATER_ANKLE = 0x400000000000,
		SURFTYPE_BITS_WATER_KNEE = 0x800000000000,
		SURFTYPE_BITS_WOOD_HOLLOW = 0x1000000000000,
		SURFTYPE_BITS_WOOD_WET = 0x2000000000000,
		SURFTYPE_BITS_WOOD_DEBRIS = 0x4000000000000,
		SURFTYPE_BITS_CUSHION = 0x8000000000000,
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
		SurfaceTypeBits surfaceTypeBits;
		unsigned int hashIndex;
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

	union SoundAliasFlags
	{
		struct _
		{
			unsigned int looping : 1;
			unsigned int isMaster : 1;
			unsigned int isSlave : 1;
			unsigned int fullDryLevel : 1;
			unsigned int noWetLevel : 1;
			unsigned int is3d : 1;
			unsigned int type : 2;
		};
		unsigned int intValue;
	};

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
		//char __padding0[2]; // padding
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
		//char __padding1[3]; // padding
		float probability;
		char u1; // value: 0-4
		//char __padding2[3]; // padding
		SndContext* sndContext;
		unsigned char sequence;
		//char __padding3[3]; // padding
		float lfePercentage;
		float centerPercentage;
		int startDelay;
		SndCurve* sndCurve;
		char __pad1[8]; // unknown
		SndCurve* lpfCurve;
		SndCurve* reverbSendCurve;
		SpeakerMap* speakerMap;
		float reverbWetMixOverride;
		float u4;
		float smartPanDistance2d;
		float smartPanDistance3d;
		float smartPanAttenuation3d;
		char __pad2[4]; // unknown
		short stereo3dAngle;
		//char __padding4[2]; // padding
		float stereo3dStart;
		float stereo3dEnd;
		unsigned char allowDoppler;
		//char __padding5[3]; // padding
		DopplerPreset* dopplerPreset;
		float u6;
		//char __padding6[4]; // padding
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
		char(*blendShapeWeightUnknown1)[3]; // 160
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

	enum activeReticleType_t : std::int32_t
	{
		VEH_ACTIVE_RETICLE_NONE = 0x0,
		VEH_ACTIVE_RETICLE_PIP_ON_A_STICK = 0x1,
		VEH_ACTIVE_RETICLE_BOUNCING_DIAMOND = 0x2,
		VEH_ACTIVE_RETICLE_COUNT = 0x3,
	};

	enum playerAnimType_t : std::uint8_t
	{
		PLAYERANIMTYPE_NONE = 0x0,
		PLAYERANIMTYPE_OTHER = 0x1,
		PLAYERANIMTYPE_PISTOL = 0x2,
		PLAYERANIMTYPE_SMG = 0x3,
		PLAYERANIMTYPE_AUTORIFLE = 0x4,
		PLAYERANIMTYPE_SNIPER = 0x5,
		PLAYERANIMTYPE_ROCKET_LAUNCHER = 0x6,
		PLAYERANIMTYPE_GRENADE = 0x7,
		PLAYERANIMTYPE_M203 = 0x8,
		PLAYERANIMTYPE_HOLD = 0x9,
		PLAYERANIMTYPE_BRIEFCASE = 0xA,
		PLAYERANIMTYPE_RIOTSHIELD = 0xB,
		PLAYERANIMTYPE_LAPTOP = 0xC,
		PLAYERANIMTYPE_THROWINGKNIFE = 0xD,
		PLAYERANIMTYPE_MINIGUN = 0xE,
		PLAYERANIMTYPE_SMG_BULLPUP = 0x1F,
		PLAYERANIMTYPE_AUTOFILE_BULLPUP = 0x10,
		PLAYERANIMTYPE_SNIPER_BULLPUP = 0x11,
		PLAYERANIMTYPE_KILLSTREAKTRIGGER = 0x12,
		PLAYERANIMTYPE_TROPHYSYSTEM = 0x13,
		PLAYERANIMTYPE_COMBATKNIFE = 0x14,
		PLAYERANIMTYPE_NUM = 0x15,
	};

	enum weapType_t : std::int32_t
	{
		WEAPCLASS_NONE = 0x0,
		WEAPCLASS_BULLET = 0x1,
		WEAPCLASS_GRENADE = 0x2,
		WEAPCLASS_PROJECTILE = 0x3,
		WEAPCLASS_RIOTSHIELD = 0x4,
		WEAPCLASS_ENERGY = 0x5,
		WEAPCLASS_NUM = 0x6,
	};

	enum weapClass_t : std::int32_t
	{
		WEAPTYPE_RIFLE = 0x1,
		WEAPTYPE_SNIPER = 0x2,
		WEAPTYPE_MG = 0x3,
		WEAPTYPE_SMG = 0x4,
		WEAPTYPE_SPREAD = 0x5,
		WEAPTYPE_PISTOL = 0x6,
		WEAPTYPE_ROCKETLAUNCHER = 0x7,
		WEAPTYPE_TURRET = 0x8,
		WEAPTYPE_THROWINGKNIFE = 0x9,
		WEAPTYPE_NON_PLAYER = 0xA,
		WEAPTYPE_ITEM = 0xB,
		WEAPTYPE_CONE = 0xC,
		WEAPTYPE_BEAM = 0xD,
		WEAPTYPE_SHIELD = 0xE,
		WEAPTYPE_HOVER = 0xF,
		WEAPTYPE_CLOAK = 0x10,
		WEAPTYPE_PING = 0x11,
		WEAPTYPE_REPULSOR = 0x12,
		WEAPTYPE_ADRENALINE = 0x13,
		WEAPTYPE_HEALTH = 0x14,
		WEAPTYPE_MUTE = 0x15,
		WEAPTYPE_UNDERWATER = 0x16,
		WEAPTYPE_BALL = 0x17,
		WEAPTYPE_NUM = 0x18,
	};

	enum weapInventoryType_t : std::int32_t
	{
		WEAPINVENTORY_PRIMARY = 0x0,
		WEAPINVENTORY_OFFHAND = 0x1,
		WEAPINVENTORY_ITEM = 0x2,
		WEAPINVENTORY_ALTMODE = 0x3,
		WEAPINVENTORY_EXCLUSIVE = 0x4,
		WEAPINVENTORY_SCAVENGER = 0x5,
		WEAPINVENTORYCOUNT = 0x6,
	};

	enum weapFireType_t : std::int32_t
	{
		WEAPON_FIRETYPE_FULLAUTO = 0x0,
		WEAPON_FIRETYPE_SINGLESHOT = 0x1,
		WEAPON_FIRETYPE_BURSTFIRE2 = 0x2,
		WEAPON_FIRETYPE_BURSTFIRE3 = 0x3,
		WEAPON_FIRETYPE_BURSTFIRE4 = 0x4,
		WEAPON_FIRETYPE_DOUBLEBARREL = 0x5,
		WEAPON_FIRETYPECOUNT = 0x6,
		WEAPON_FIRETYPE_BURSTFIRE_FIRST = 0x2,
		WEAPON_FIRETYPE_BURSTFIRE_LAST = 0x4,
	};

	enum PenetrateType : std::uint32_t
	{
		PENETRATE_TYPE_NONE = 0x0,
		PENETRATE_TYPE_SMALL = 0x1,
		PENETRATE_TYPE_MEDIUM = 0x2,
		PENETRATE_TYPE_LARGE = 0x3,
		PENETRATE_TYPE_COUNT = 0x4,
	};

	enum ImpactType : std::int32_t
	{

	};

	enum weapStance_t : std::int32_t
	{
		WEAPSTANCE_STAND = 0x0,
		WEAPSTANCE_DUCK = 0x1,
		WEAPSTANCE_PRONE = 0x2,
		WEAPSTANCE_NUM = 0x3,
	};

	enum OffhandClass : std::uint32_t
	{
		OFFHAND_CLASS_NONE = 0x0,
		OFFHAND_CLASS_FRAG_GRENADE = 0x1,
		OFFHAND_CLASS_SMOKE_GRENADE = 0x2,
		OFFHAND_CLASS_FLASH_GRENADE = 0x3,
		OFFHAND_CLASS_OTHER = 0x9,
		OFFHAND_CLASS_COUNT = 0xA,
	};

	enum weapProjExposion_t : std::int32_t
	{
		WEAPPROJEXP_GRENADE = 0x0,
		WEAPPROJEXP_ROCKET = 0x1,
		WEAPPROJEXP_FLASHBANG = 0x2,
		WEAPPROJEXP_NONE = 0x3,
		WEAPPROJEXP_DUD = 0x4,
		WEAPPROJEXP_SMOKE = 0x5,
		WEAPPROJEXP_HEAVY = 0x6,
		WEAPPROJEXP_NUM = 0x7,
	};

	enum weapAdsFireMode_t : std::int32_t
	{
		WEAPADSFIREMODE_NUM = 0x3,
	};

	enum weapGreebleType_t : std::int32_t
	{
		WEAPGREEBLE_NONE = 0x0,
		WEAPGREEBLE_ACCURACYLEVEL1 = 0x1,
		WEAPGREEBLE_ACCURACYLEVEL2 = 0x2,
		WEAPGREEBLE_FIRERATELEVEL1 = 0x3,
		WEAPGREEBLE_FIRERATELEVEL2 = 0x4,
		WEAPGREEBLE_NUM = 0x5,
	};

	enum weapAutoReloadType_t : std::int32_t
	{

	};

	enum weapFireBarrels_t : std::int32_t
	{

	};

	enum weapFireTimeInterpolation_t : std::int32_t
	{

	};

	enum WeaponSlotRestriction : std::int32_t
	{
		SLOT_RESTRICTION_NONE = 0x0,
		SLOT_RESTRICTION_OPEN = 0x1,
		SLOT_RESTRICTION_PRESET = 0x2,
		SLOT_RESTRICTION_COUNT = 0x3,
	};

	enum AttachmentType : std::int32_t
	{
		ATTACHMENT_SCOPE = 0x0,
		ATTACHMENT_UNDERBARREL = 0x1,
		ATTACHMENT_OTHER = 0x2,
		ATTACHMENT_COUNT = 0x3,
	};

	struct AttChargeInfo
	{
		char __pad0[28];
	}; static_assert(sizeof(AttChargeInfo) == 28);

	struct AttHybridSettings
	{
		char __pad0[72];
	}; static_assert(sizeof(AttHybridSettings) == 72);

	union WAFieldParm
	{
		const char* a;
	};

	struct WAField
	{
		char unknown;
		char fieldType;
		WAFieldParm parm;
	}; static_assert(sizeof(WAField) == 16);

	struct WeaponAttachment
	{
		union
		{
			const char* szInternalName;
			const char* name;
		};
		const char* szDisplayName;
		AttachmentType type;
		weapType_t weaponType;
		weapClass_t weapClass;
		XModel** worldModels; // (2 xmodels)
		XModel** viewModels; // (2 xmodels)
		XModel** reticleViewModels; // (64 xmodels)
		snd_alias_list_t** unknownSounds1; /// (53 sounds)
		snd_alias_list_t** unknownSounds2; /// (53 sounds)
		AttChargeInfo* chargeInfo;
		AttHybridSettings* hybridSettings;
		scr_string_t* stringArray1; // (4 strings)
		scr_string_t* stringArray2; // (4 strings)
		unsigned short* unknownArray;
		WAField* waFields;
		unsigned int unknownCount;
		char __pad0[20];
		// TODO:
	}; static_assert(sizeof(WeaponAttachment) == 0x90);

	struct AnimOverrideEntry
	{
		unsigned short attachment1;
		unsigned short attachment2;
		XAnimParts* overrideAnim;
		XAnimParts* altmodeAnim;
		//unsigned int animTreeType;
		int animTime;
		int altTime;
	}; static_assert(sizeof(AnimOverrideEntry) == 32);

	struct SoundOverrideEntry
	{
		unsigned short attachment1;
		unsigned short attachment2;
		snd_alias_list_t* overrideSound;
		snd_alias_list_t* altmodeSound;
		//unsigned int soundType;
	}; static_assert(sizeof(SoundOverrideEntry) == 24);

	struct FXOverrideEntry
	{
		unsigned short attachment1;
		unsigned short attachment2;
		FxEffectDef* overrideFX;
		FxEffectDef* altmodeFX;
		//unsigned int fxType;
	}; static_assert(sizeof(FXOverrideEntry) == 24);

	struct ReloadStateTimerEntry
	{
		int attachment;
		int reloadAddTime;
		int reloadEmptyAddTime;
		int reloadStartAddTime;
	}; static_assert(sizeof(ReloadStateTimerEntry) == 16);

	struct NoteTrackToSoundEntry
	{
		int attachment;
		scr_string_t* notetrackSoundMapKeys;
		scr_string_t* notetrackSoundMapValues;
	}; static_assert(sizeof(NoteTrackToSoundEntry) == 24);

	struct TracerDef
	{
		const char* name;
		Material* material;
		FxEffectDef* effect;
		unsigned int drawInterval;
		float speed;
		float beamLength;
		float beamWidth;
		float screwRadius;
		float screwDist;
		float colors[5][4];
	}; static_assert(sizeof(TracerDef) == 0x80);

	struct LaserDef
	{
		const char* name;
		Material* laserMaterial;
		Material* laserLightMaterial;
		FxEffectDef* effect;
		LaserDef* altLaser;
		scr_string_t* value;
		char __pad0[104];
	}; static_assert(sizeof(LaserDef) == 0x98);

	struct TurretHydraulicSettings
	{
		float minVelocity;
		float maxVelocity; // unused or padding
		snd_alias_list_t* verticalSound;
		snd_alias_list_t* verticalStopSound;
		snd_alias_list_t* horizontalSound;
		snd_alias_list_t* horizontalStopSound;
	}; static_assert(sizeof(TurretHydraulicSettings) == 40);

	enum weapOverlayReticle_t : std::int32_t
	{
		WEAPOVERLAYRETICLE_NONE = 0x0,
		WEAPOVERLAYRETICLE_CROSSHAIR = 0x1,
		WEAPOVERLAYRETICLE_NUM = 0x2,
	};

	struct ADSOverlay
	{
		Material* shader;
		Material* shaderLowRes;
		Material* shaderEMP;
		Material* shaderEMPLowRes;
		weapOverlayReticle_t reticle;
		float width;
		float height;
		float widthSplitscreen;
		float heightSplitscreen;
	}; static_assert(sizeof(ADSOverlay) == 0x38);

	enum weaponIconRatioType_t : std::int32_t
	{
		WEAPON_ICON_RATIO_1TO1 = 0x0,
		WEAPON_ICON_RATIO_2TO1 = 0x1,
		WEAPON_ICON_RATIO_4TO1 = 0x2,
		WEAPON_ICON_RATIO_COUNT = 0x3,
	};

	enum WeapStickinessType : std::int32_t
	{
		WEAPSTICKINESS_NONE = 0x0,
		WEAPSTICKINESS_ALL = 0x1,
		WEAPSTICKINESS_ALL_ORIENT = 0x2,
		WEAPSTICKINESS_GROUND = 0x3,
		WEAPSTICKINESS_GROUND_WITH_YAW = 0x4,
		WEAPSTICKINESS_KNIFE = 0x5,
		WEAPSTICKINESS_COUNT = 0x6,
	};

	enum guidedMissileType_t : std::int32_t
	{
		MISSILE_GUIDANCE_NONE = 0x0,
		MISSILE_GUIDANCE_SIDEWINDER = 0x1,
		MISSILE_GUIDANCE_HELLFIRE = 0x2,
		MISSILE_GUIDANCE_JAVELIN = 0x3,
		MISSILE_GUIDANCE_UNKNOWN0 = 0x4,
		MISSILE_GUIDANCE_UNKNOWN1 = 0x5,
		MISSILE_GUIDANCE_UNKNOWN2 = 0x6,
		MISSILE_GUIDANCE_COUNT = 0x7,
	};

	enum WeapOverlayInteface_t : std::int32_t
	{
		WEAPOVERLAYINTERFACE_NONE = 0x0,
		WEAPOVERLAYINTERFACE_JAVELIN = 0x1,
		WEAPOVERLAYINTERFACE_TURRETSCOPE = 0x2,
		WEAPOVERLAYINTERFACECOUNT = 0x3,
	};

	enum weapAnimFiles_t : std::int32_t
	{
		WEAP_ANIM_INVALID = -1,
		WEAP_ANIM_ROOT = 0,
		WEAP_ANIM_IDLE = 1,
		WEAP_ANIM_EMPTY_IDLE = 2,
		WEAP_ANIM_FIRE = 3,
		WEAP_ANIM_HOLD_FIRE = 4,
		WEAP_ANIM_LASTSHOT = 5,
		WEAP_ANIM_RECHAMBER = 6,
		WEAP_ANIM_GRENADE_PRIME = 7,
		WEAP_ANIM_GRENADE_PRIME_READY_TO_THROW = 8,
		WEAP_ANIM_MELEE_SWIPE = 9,
		WEAP_ANIM_MELEE_HIT = 10,
		WEAP_ANIM_MELEE_FATAL = 11,
		WEAP_ANIM_MELEE_MISS = 12,
		WEAP_ANIM_MELEE_VICTIM_CROUCHING_HIT = 13,
		WEAP_ANIM_MELEE_VICTIM_CROUCHING_FATAL = 14,
		WEAP_ANIM_MELEE_VICTIM_CROUCHING_MISS = 15,
		WEAP_ANIM_MELEE_ALT_STANDING = 16,
		WEAP_ANIM_MELEE_ALT_CROUCHING = 17,
		WEAP_ANIM_MELEE_ALT_PRONE = 18,
		WEAP_ANIM_MELEE_ALT_JUMPING = 19,
		WEAP_ANIM_MELEE_ALT_STANDING_VICTIM_CROUCHING = 20,
		WEAP_ANIM_MELEE_ALT_CROUCHING_VICTIM_CROUCHING = 21,
		WEAP_ANIM_MELEE_ALT_PRONE_VICTIM_CROUCHING = 22,
		WEAP_ANIM_MELEE_ALT_JUMPING_VICTIM_CROUCHING = 23,
		WEAP_ANIM_RELOAD = 24,
		WEAP_ANIM_RELOAD_EMPTY = 25,
		WEAP_ANIM_RELOAD_START = 26,
		WEAP_ANIM_RELOAD_END = 27,
		WEAP_ANIM_FAST_RELOAD = 28,
		WEAP_ANIM_FAST_RELOAD_EMPTY = 29,
		WEAP_ANIM_FAST_RELOAD_START = 30,
		WEAP_ANIM_FAST_RELOAD_END = 31,
		WEAP_ANIM_DUALMAG_RELOAD = 32,
		WEAP_ANIM_DUALMAG_RELOAD_EMPTY = 33,
		WEAP_ANIM_SPEED_RELOAD = 34,
		WEAP_ANIM_RELOAD_FROM_ALT = 35,
		WEAP_ANIM_RAISE = 36,
		WEAP_ANIM_FIRST_RAISE = 37,
		WEAP_ANIM_BREACH_RAISE = 38,
		WEAP_ANIM_DROP = 39,
		WEAP_ANIM_ALT_RAISE = 40,
		WEAP_ANIM_ALT_DROP = 41,
		WEAP_ANIM_ALT_OVERRIDE = 42,
		WEAP_ANIM_QUICK_RAISE = 43,
		WEAP_ANIM_QUICK_DROP = 44,
		WEAP_ANIM_EMPTY_RAISE = 45,
		WEAP_ANIM_EMPTY_DROP = 46,
		WEAP_ANIM_HYBRID_SIGHT_ON = 47,
		WEAP_ANIM_HYBRID_SIGHT_OFF = 48,
		WEAP_ANIM_SPRINT_IN = 49,
		WEAP_ANIM_SPRINT_IN_FROM_SLIDE = 50,
		WEAP_ANIM_SPRINT_IN_CANCEL = 51,
		WEAP_ANIM_SPRINT_LOOP = 52,
		WEAP_ANIM_SPRINT_OUT = 53,
		WEAP_ANIM_SPRINTANDFIRE_IN = 54,
		WEAP_ANIM_SPRINTANDFIRE_LOOP = 55,
		WEAP_ANIM_SPRINTANDFIRE_OUT = 56,
		WEAP_ANIM_STUNNED_START = 57,
		WEAP_ANIM_STUNNED_LOOP = 58,
		WEAP_ANIM_STUNNED_END = 59,
		WEAP_ANIM_THROWBACK = 60,
		WEAP_ANIM_DETONATE = 61,
		WEAP_ANIM_NIGHTVISION_WEAR = 62,
		WEAP_ANIM_NIGHTVISION_REMOVE = 63,
		WEAP_ANIM_ADS_FIRE = 64,
		WEAP_ANIM_ADS_LASTSHOT = 65,
		WEAP_ANIM_ADS_RECHAMBER = 66,
		WEAP_ANIM_BLAST_FRONT = 67,
		WEAP_ANIM_BLAST_RIGHT = 68,
		WEAP_ANIM_BLAST_BACK = 69,
		WEAP_ANIM_BLAST_LEFT = 70,
		WEAP_ANIM_SLIDE_IN = 71,
		WEAP_ANIM_SLIDE_LOOP = 72,
		WEAP_ANIM_SLIDE_OUT_TO_SPRINT = 73,
		WEAP_ANIM_SLIDE_OUT = 74,
		WEAP_ANIM_SLIDE_AND_FIRE_IN = 75,
		WEAP_ANIM_SLIDE_AND_FIRE_LOOP = 76,
		WEAP_ANIM_SLIDE_AND_FIRE_OUT = 77,
		WEAP_ANIM_HIGH_JUMP_IN = 78,
		WEAP_ANIM_HIGH_JUMP_DROP_IN = 79,
		WEAP_ANIM_HIGH_JUMP_DROP_LOOP = 80,
		WEAP_ANIM_HIGH_JUMP_DROP_LAND = 81,
		WEAP_ANIM_DODGE_GROUND_BACK = 82,
		WEAP_ANIM_DODGE_GROUND_LEFT = 83,
		WEAP_ANIM_DODGE_GROUND_RIGHT = 84,
		WEAP_ANIM_DODGE_AIR_FORWARD = 85,
		WEAP_ANIM_DODGE_AIR_BACK = 86,
		WEAP_ANIM_DODGE_AIR_LEFT = 87,
		WEAP_ANIM_DODGE_AIR_RIGHT = 88,
		WEAP_ANIM_LAND_DIP = 89,
		WEAP_ANIM_RECOIL_SETTLE = 90,
		WEAP_ANIM_SWIM_LOOP = 91,
		WEAP_ANIM_MANTLE_UP_64 = 92,
		WEAP_ANIM_MANTLE_UP_56 = 93,
		WEAP_ANIM_MANTLE_UP_48 = 94,
		WEAP_ANIM_MANTLE_UP_40 = 95,
		WEAP_ANIM_MANTLE_UP_32 = 96,
		WEAP_ANIM_MANTLE_UP_24 = 97,
		WEAP_ANIM_MANTLE_UP_16 = 98,
		WEAP_ANIM_MANTLE_OVER_64 = 99,
		WEAP_ANIM_MANTLE_OVER_56 = 100,
		WEAP_ANIM_MANTLE_OVER_48 = 101,
		WEAP_ANIM_MANTLE_OVER_40 = 102,
		WEAP_ANIM_MANTLE_OVER_32 = 103,
		WEAP_ANIM_MANTLE_OVER_24 = 104,
		WEAP_ANIM_MANTLE_OVER_16 = 105,
		WEAP_ANIM_GOLIATH_ENTRY = 106,
		WEAP_ANIM_OFFHAND_SWITCH = 107,
		WEAP_ANIM_HEAT_COOLDOWN_IN = 108,
		WEAP_ANIM_HEAT_COOLDOWN_OUT = 109,
		WEAP_ANIM_OVERHEAT_OUT = 110,
		WEAP_ANIM_SCRIPTED = 111,
		WEAP_ANIM_INSPECTION = 112,
		WEAP_ANIM_RELOAD_MULTIPLE_1 = 113,
		WEAP_ANIM_RELOAD_MULTIPLE_2 = 114,
		WEAP_ANIM_RELOAD_MULTIPLE_3 = 115,
		WEAP_ANIM_RELOAD_MULTIPLE_4 = 116,
		WEAP_ANIM_RELOAD_MULTIPLE_5 = 117,
		WEAP_ANIM_RELOAD_MULTIPLE_6 = 118,
		WEAP_ANIM_RELOAD_MULTIPLE_7 = 119,
		WEAP_ANIM_RELOAD_MULTIPLE_8 = 120,
		WEAP_ANIM_RELOAD_MULTIPLE_FAST_1 = 121,
		WEAP_ANIM_RELOAD_MULTIPLE_FAST_2 = 122,
		WEAP_ANIM_RELOAD_MULTIPLE_FAST_3 = 123,
		WEAP_ANIM_RELOAD_MULTIPLE_FAST_4 = 124,
		WEAP_ANIM_RELOAD_MULTIPLE_FAST_5 = 125,
		WEAP_ANIM_RELOAD_MULTIPLE_FAST_6 = 126,
		WEAP_ANIM_RELOAD_MULTIPLE_FAST_7 = 127,
		WEAP_ANIM_RELOAD_MULTIPLE_FAST_8 = 128,
		WEAP_ANIM_ADS_UP = 129,
		WEAP_ANIM_ADS_DOWN = 130,
		WEAP_ANIM_RECOIL = 131,
		WEAP_ALT_ANIM_ADJUST = 132,
		WEAP_ANIM_ADDITIVE_ADS_ROOT = 133,
		WEAP_ANIM_ADDITIVE_ADS_UP = 134,
		WEAP_ANIM_ADDITIVE_HYBRID_SIGHT_UP_ROOT = 135,
		WEAP_ANIM_ADDITIVE_HYBRID_SIGHT_UP = 136,
		WEAP_ANIM_ADDITIVE_DRAG_LEFT_ROOT = 137,
		WEAP_ANIM_ADDITIVE_DRAG_LEFT = 138,
		WEAP_ANIM_ADDITIVE_DRAG_RIGHT_ROOT = 139,
		WEAP_ANIM_ADDITIVE_DRAG_RIGHT = 140,
		WEAP_ANIM_ADDITIVE_DRAG_UP_ROOT = 141,
		WEAP_ANIM_ADDITIVE_DRAG_UP = 142,
		WEAP_ANIM_ADDITIVE_DRAG_DOWN_ROOT = 143,
		WEAP_ANIM_ADDITIVE_DRAG_DOWN = 144,
		WEAP_ANIM_ADDITIVE_SWIM_FORWARD_ROOT = 145,
		WEAP_ANIM_ADDITIVE_SWIM_FORWARD = 146,
		WEAP_ANIM_ADDITIVE_SWIM_BACKWARD_ROOT = 147,
		WEAP_ANIM_ADDITIVE_SWIM_BACKWARD = 148,
		WEAP_ANIM_ADDITIVE_JUMP_ROOT = 149,
		WEAP_ANIM_ADDITIVE_JUMP = 150,
		WEAP_ANIM_ADDITIVE_JUMP_BOOST = 151,
		WEAP_ANIM_ADDITIVE_JUMP_LAND_ROOT = 152,
		WEAP_ANIM_ADDITIVE_JUMP_LAND = 153,
		WEAP_ANIM_ADDITIVE_JUMP_LAND_HEAVY = 154,
		WEAP_ANIM_ADDITIVE_WALK_ROOT = 155,
		WEAP_ANIM_ADDITIVE_WALK = 156,
		WEAP_ANIM_ADDITIVE_HEAT_COOLDOWN_LOOP_ROOT = 157,
		WEAP_ANIM_ADDITIVE_HEAT_COOLDOWN_LOOP = 158,
		WEAP_ANIM_ADDITIVE_OVERHEAT_IN_ROOT = 159,
		WEAP_ANIM_ADDITIVE_OVERHEAT_IN = 160,
		WEAP_ANIM_ADDITIVE_OVERHEAT_LOOP_ROOT = 161,
		WEAP_ANIM_ADDITIVE_OVERHEAT_LOOP = 162,
		WEAP_ANIM_ADDITIVE_CRAWL_IN_ROOT = 163,
		WEAP_ANIM_ADDITIVE_CRAWL_IN = 164,
		WEAP_ANIM_ADDITIVE_CRAWL_LOOP_ROOT = 165,
		WEAP_ANIM_ADDITIVE_CRAWL_LOOP = 166,
		WEAP_ANIM_ADDITIVE_CRAWL_LOOP_BACK_ROOT = 167,
		WEAP_ANIM_ADDITIVE_CRAWL_LOOP_BACK = 168,
		WEAP_ANIM_ADDITIVE_CRAWL_LOOP_LEFT_ROOT = 169,
		WEAP_ANIM_ADDITIVE_CRAWL_LOOP_LEFT = 170,
		WEAP_ANIM_ADDITIVE_CRAWL_LOOP_RIGHT_ROOT = 171,
		WEAP_ANIM_ADDITIVE_CRAWL_LOOP_RIGHT = 172,
		WEAP_ANIM_ADDITIVE_PRONE_DROP_ROOT = 173,
		WEAP_ANIM_ADDITIVE_PRONE_DROP = 174,
		WEAP_ANIM_ADDITIVE_EMPTY_ROOT = 175,
		WEAP_ANIM_ADDITIVE_EMPTY = 176,
		WEAP_ANIM_ADDITIVE_MANTLE_ROOT = 177,
		WEAP_ANIM_ADDITIVE_MANTLE = 178,
		WEAP_ANIM_ADDITIVE_LOW_MANTLE_ROOT = 179,
		WEAP_ANIM_ADDITIVE_MANTLE_UP_24 = 180,
		WEAP_ANIM_ADDITIVE_MANTLE_UP_16 = 181,
		WEAP_ANIM_ADDITIVE_MANTLE_OVER_24 = 182,
		WEAP_ANIM_ADDITIVE_MANTLE_OVER_16 = 183,
		WEAP_ANIM_ADDITIVE_SHOT_CHARGE_IN_ROOT = 184,
		WEAP_ANIM_ADDITIVE_SHOT_CHARGE_IN = 185,
		WEAP_ANIM_ADDITIVE_SHOT_CHARGE_LOOP_ROOT = 186,
		WEAP_ANIM_ADDITIVE_SHOT_CHARGE_LOOP = 187,
		WEAP_ANIM_ADDITIVE_SCRIPTED_ROOT = 188,
		WEAP_ANIM_ADDITIVE_SCRIPTED = 189,
		NUM_WEAP_ANIMS = 190,
	};

	struct StateTimers
	{
		int fireDelay; // 1640 * x
		int meleeDelay; // 1644 * x
		int meleeChargeDelay; // 1648 * x
		int detonateDelay; // 1652 * x
		int fireTime; // 1656 * x
		int rechamberTime; // 1660 * x
		int rechamberTimeOneHanded; // 1664 * x
		int rechamberBoltTime; // 1668 * x
		int holdFireTime; // 1672 * x
		int grenadePrimeReadyToThrowTime; // 1676 * x
		int detonateTime; // 1680 * x
		int meleeTime; // 1684 * x
		int meleeChargeTime; // 1688 * x
		int reloadTime; // 1692 * x
		int reloadShowRocketTime; // 1696 * x
		int reloadEmptyTime; // 1700 * x
		int reloadAddTime; // 1704 * x
		int reloadEmptyAddTime; // 1708 * x
		int reloadStartTime; // 1712 * x
		int reloadStartAddTime; // 1716 * x
		int reloadEndTime; // 1720 * x
		int reloadTimeDualWield; // 1724 * x
		int reloadAddTimeDualWield; // 1728 * x
		int reloadEmptyDualMag; // 1732 * x
		int reloadEmptyAddTimeDualMag; // 1736 * x
		int u25; // 1740 * x // (unused)
		int u26; // 1744 * x // (unused)
		int dropTime; // 1748 * x
		int raiseTime; // 1752 * x
		int altDropTime; // 1756 * x
		int altRaiseTime; // 1760 * x
		int quickDropTime; // 1764 * x
		int quickRaiseTime; // 1768 * x
		int firstRaiseTime; // 1772 * x
		int breachRaiseTime; // 1776 * x
		int emptyRaiseTime; // 1780 * x
		int emptyDropTime; // 1784 * x
		int sprintInTime; // 1788 * x
		int sprintLoopTime; // 1792 * x
		int sprintOutTime; // 1796 * x
		int stunnedTimeBegin; // 1800 * x
		int stunnedTimeLoop; // 1804 * x
		int stunnedTimeEnd; // 1808 * x
		int nightVisionWearTime; // 1812 * x
		int nightVisionWearTimeFadeOutEnd; // 1816 * x
		int nightVisionWearTimePowerUp; // 1820 * x
		int nightVisionRemoveTime; // 1824 * x
		int nightVisionRemoveTimePowerDown; // 1828 * x
		int nightVisionRemoveTimeFadeInStart; // 1832 * x
		int aiFuseTime; // 1836 * x
		int fuseTime; // 1840 * x
		int missileTime; // 1844 * x
		int primeTime; // 1848 * x
		bool bHoldFullPrime; // 1852 * x
		int blastFrontTime; // 1856 * x
		int blastRightTime; // 1860 * x
		int blastBackTime; // 1864 * x
		int blastLeftTime; // 1868 * x
		int u58; // 1872 * x (unused)
		int u59; // 1876 * x (unused)
		int u60; // 1880 * x (unused)
		int u61; // 1884 * x (unused)
		int u62; // 1888 * x (unused)
		int u63; // 1892 * x (unused)
		int u64; // 1896 * x (unused)
		int u65; // 1900 * x (unused)
		int u66; // 1904 * x (unused)
		int u67; // 1908 * x (unused)
		int u68; // 1912 * x (unused)
		int offhandSwitchTime; // 1916 * x
		int u70; // 1920 * x (unknown)
		int u71; // 1924 * x (unknown)
		int u72; // 1928 * x (unknown)
		int u73; // 1932 * x (unknown)
		int u74; // 1936 * x (unknown)
	}; static_assert(sizeof(StateTimers) == 300);

	struct WeaponDef
	{
		union
		{
			const char* szInternalName;
			const char* name;
		};
		const char* szDisplayName; // 8
		const char* szOverlayName; // 16
		XModel** gunModel; // 24 (2 xmodels)
		XModel* handModel; // 32
		XModel* unknownModel; // 40
		XModel** reticleViewModels; // 48 (64 xmodels)
		const char* szModeName; // 56
		XAnimParts** szXAnimsRightHanded; // 64 (190 xanims)
		XAnimParts** szXAnimsLeftHanded; // 72 (190 xanims)
		scr_string_t* hideTags; // 80 (32 xstrings)
		WeaponAttachment** attachments; // 88 (weaponDef + 1332 attachments)
		XAnimParts** szXAnims; // 96 (190 xanims)
		AnimOverrideEntry* animOverrides; // 104 (weaponDef + 1333 overrides)
		SoundOverrideEntry* soundOverrides; // 112 (weaponDef + 1334 overrides)
		FXOverrideEntry* fxOverrides; // 120 (weaponDef + 1335 overrides)
		ReloadStateTimerEntry* reloadOverrides; // 128 (weaponDef + 1336 overrides)
		NoteTrackToSoundEntry* notetrackOverrides; // 136 (weaponDef + 1337 overrides)
		scr_string_t* notetrackSoundMapKeys; // 144 (36 xstrings)
		scr_string_t* notetrackSoundMapValues; // 152 (36 xstrings)
		scr_string_t* notetrackRumbleMapKeys; // 160 (16 xstrings)
		scr_string_t* notetrackRumbleMapValues; // 168 (16 xstrings)
		scr_string_t* notetrackFXMapKeys; // 176 (16 xstrings)
		FxEffectDef** notetrackFXMapValues; // 184 (16 effects)
		scr_string_t* notetrackFXMapTagValues; // 192 (16 xstrings)
		scr_string_t* notetrackUnknownKeys; // 200 (16 xstrings)
		char* notetrackUnknown; // 208 (16 chars)
		scr_string_t* notetrackUnknownValues; // 216 (16 xstrings)
		const char* szAltWeaponName; // 224
		FxEffectDef* viewFlashEffect; // 232
		FxEffectDef* viewBodyFlashEffect; // 240
		FxEffectDef* worldFlashEffect; // 248
		FxEffectDef* viewFlashADSEffect; // 256
		FxEffectDef* viewBodyFlashADSEffect; // 264
		FxEffectDef* effect06; // 272
		FxEffectDef* effect07; // 280
		FxEffectDef* effect08; // 288
		FxEffectDef* effect09; // 296
		FxEffectDef* effect10; // 304
		FxEffectDef* effect11; // 312
		FxEffectDef* effect12; // 320
		snd_alias_list_t* pickupSound; // 328 (74 sounds)
		snd_alias_list_t* pickupSoundPlayer; // 336
		snd_alias_list_t* ammoPickupSound; // 344
		snd_alias_list_t* ammoPickupSoundPlayer; // 352
		snd_alias_list_t* projectileSound; // 360
		snd_alias_list_t* pullbackSound; // 368
		snd_alias_list_t* pullbackSoundPlayer; // 376
		snd_alias_list_t* pullbackSoundQuick; // 384
		snd_alias_list_t* pullbackSoundQuickPlayer; // 392
		snd_alias_list_t* fireSound; // 400
		snd_alias_list_t* fireSoundPlayer; // 408
		snd_alias_list_t* fireSoundPlayerAkimbo; // 416
		snd_alias_list_t* sound13; // 424
		snd_alias_list_t* sound14; // 432
		snd_alias_list_t* sound15; // 440
		snd_alias_list_t* sound16; // 448
		snd_alias_list_t* fireLoopSound; // 456
		snd_alias_list_t* fireLoopSoundPlayer; // 464
		snd_alias_list_t* sound19; // 472
		snd_alias_list_t* sound20; // 480
		snd_alias_list_t* sound21; // 488
		snd_alias_list_t* sound22; // 496
		snd_alias_list_t* fireLoopEndPointSound; // 504
		snd_alias_list_t* fireLoopEndPointSoundPlayer; // 512
		snd_alias_list_t* fireStopSound; // 520
		snd_alias_list_t* fireStopSoundPlayer; // 528
		snd_alias_list_t* sound27; // 536
		snd_alias_list_t* sound28; // 544
		snd_alias_list_t* sound29; // 552
		snd_alias_list_t* sound30; // 560
		snd_alias_list_t* fireLastShotSound; // 568
		snd_alias_list_t* fireLastShotSoundPlayer; // 576
		snd_alias_list_t* fireFirstSound; // 584
		snd_alias_list_t* fireFirstSoundPlayer; // 592
		snd_alias_list_t* fireLastSound; // 600
		snd_alias_list_t* fireLastSoundPlayer; // 608
		snd_alias_list_t* emptyFireSound; // 616
		snd_alias_list_t* emptyFireSoundPlayer; // 624
		snd_alias_list_t* sound39; // 632
		snd_alias_list_t* meleeSwipeSound; // 640
		snd_alias_list_t* meleeSwipeSoundPlayer; // 648
		snd_alias_list_t* meleeHitSound; // 656
		snd_alias_list_t* meleeHitSoundPlayer; // 664
		snd_alias_list_t* meleeMissSound; // 672
		snd_alias_list_t* meleeMissSoundPlayer; // 680
		snd_alias_list_t* rechamberSound; // 688
		snd_alias_list_t* rechamberSoundPlayer; // 696
		snd_alias_list_t* reloadSound; // 704
		snd_alias_list_t* reloadSoundPlayer; // 712
		snd_alias_list_t* reloadEmptySound; // 720
		snd_alias_list_t* reloadEmptySoundPlayer; // 728
		snd_alias_list_t* reloadStartSound; // 736
		snd_alias_list_t* reloadStartSoundPlayer; // 744
		snd_alias_list_t* reloadEndSound; // 752
		snd_alias_list_t* reloadEndSoundPlayer; // 760
		snd_alias_list_t* detonateSound; // 768
		snd_alias_list_t* detonateSoundPlayer; // 776
		snd_alias_list_t* nightVisionWearSound; // 784
		snd_alias_list_t* nightVisionWearSoundPlayer; // 792
		snd_alias_list_t* nightVisionRemoveSound; // 800
		snd_alias_list_t* nightVisionRemoveSoundPlayer; // 808
		snd_alias_list_t* raiseSound; // 816
		snd_alias_list_t* raiseSoundPlayer; // 824
		snd_alias_list_t* sound64; // 832
		snd_alias_list_t* sound65; // 840
		snd_alias_list_t* sound66; // 848
		snd_alias_list_t* sound67; // 856
		snd_alias_list_t* putawaySound; // 864
		snd_alias_list_t* putawaySoundPlayer; // 872
		snd_alias_list_t* sound70; // 880
		snd_alias_list_t* sound71; // 888
		snd_alias_list_t* adsEnterSoundPlayer; // 896
		snd_alias_list_t* adsLeaveSoundPlayer; // 904
		snd_alias_list_t* adsCrosshairEnemySound; // 912
		snd_alias_list_t** bounceSound; // 920 (53 sounds)
		snd_alias_list_t** rollingSound; // 928 (53 sounds)
		FxEffectDef* viewShellEjectEffect; // 936
		FxEffectDef* worldShellEjectEffect; // 944
		FxEffectDef* viewLastShotEjectEffect; // 952
		FxEffectDef* worldLastShotEjectEffect; // 960
		FxEffectDef* viewMagEjectEffect; // 968
		Material* reticleCenter; // 976
		Material* reticleSide; // 984
		XModel** worldModel; // 992 (2 xmodels)
		XModel* worldClipModel; // 1000
		XModel* rocketModel; // 1008
		XModel* knifeModel; // 1016
		XModel* worldKnifeModel; // 1024
		Material* hudIcon; // 1032
		Material* pickupIcon; // 1040
		Material* unknownIcon2; // 1048
		Material* unknownIcon3; // 1056
		Material* unknownIcon4; // 1064
		Material* ammoCounterIcon; // 1072
		const char* szAmmoName; // 1080
		const char* szClipName; // 1088
		const char* szSharedAmmoCapName; // 1096
		PhysCollmap* physCollmap; // 1104
		PhysPreset* physPreset; // 1112
		const char* szUseHintString; // 1120
		const char* dropHintString; // 1128
		float* locationDamageMultipliers; // 1136 (22 floats)
		const char* fireRumble; // 1144
		const char* fireMedRumble; // 1152
		const char* fireHighRumble; // 1160
		const char* meleeImpactRumble; // 1168
		TracerDef* tracer1; // 1176
		TracerDef* tracer2; // 1184
		LaserDef* laser; // 1192
		snd_alias_list_t* turretOverheatSound; // 1200
		FxEffectDef* turretOverheatEffect; // 1208
		const char* turretBarrelSpinRumble; // 1216
		snd_alias_list_t* turretBarrelSpinMaxSnd; // 1224
		snd_alias_list_t* turretBarrelSpinUpSnd[4]; // 1232
		snd_alias_list_t* turretBarrelSpinDownSnd[4]; // 1264
		snd_alias_list_t* missileConeSoundAlias; // 1296
		snd_alias_list_t* missileConeSoundAliasAtBase; // 1304
		XModel* stowOffsetModel; // 1312
		TurretHydraulicSettings* turretHydraulicSettings; // 1320
		int altWeapon; // 1328
		unsigned char numWeaponAttachments; // 1332
		unsigned char numAnimOverrides; // 1333
		unsigned char numSoundOverrides; // 1334
		unsigned char numFXOverrides; // 1335
		unsigned char numReloadStateTimerOverrides; // 1336
		unsigned char numNotetrackOverrides; // 1337
		playerAnimType_t playerAnimType; // 1338
		char __pad000[1];
		weapType_t weapType; // 1340
		weapClass_t weapClass; // 1344
		PenetrateType penetrateType; // 1348
		float penetrateDepth; // 1352
		ImpactType impactType; // 1356
		weapInventoryType_t inventoryType; // 1360
		weapFireType_t fireType; // 1364
		weapFireBarrels_t fireBarrels; // 1368
		weapAdsFireMode_t adsFireMode; // 1372
		float burstFireCooldown; // 1376
		weapGreebleType_t greebleType; // 1380
		weapAutoReloadType_t autoReloadType; // 1384
		WeaponSlotRestriction slotRestriction; // 1388
		OffhandClass offhandClass; // 1392
		weapStance_t stance; // 1396
		int reticleCenterSize; // 1400
		int iReticleSideSize; // 1404
		int iReticleMinOfs; // 1408
		activeReticleType_t activeReticleType; // 1412
		float vStandMove[3]; // 1416 1420 1424
		float vStandRot[3]; // 1428 1432 1436
		float strafeMove[3]; // 1440 1444 1448
		float strafeRot[3]; // 1452 1456 1460
		float vDuckedOfs[3]; // 1464 1468 1472
		float vDuckedMove[3]; // 1476 1480 1484
		float vDuckedRot[3]; // 1488 1492 1496
		float vProneOfs[3]; // 1500 1504 1508
		float vProneMove[3]; // 1512 1516 1520
		float vProneRot[3]; // 1524 1528 1532
		float fPosMoveRate; // 1536
		float fPosProneMoveRate; // 1540
		float fStandMoveMinSpeed; // 1544
		float fDuckedMoveMinSpeed; // 1548
		float fProneMoveMinSpeed; // 1552
		float fPosRotRate; // 1556
		float fPosProneRotRate; // 1560
		weaponIconRatioType_t hudIconRatio; // 1564
		weaponIconRatioType_t pickupIconRatio; // 1568
		weaponIconRatioType_t ammoCounterIconRatio; // 1572
		int iAmmoCounterClip; // 1576
		int iStartAmmo; // 1580
		int iAmmoIndex; // 1584 (runtime variable)
		char iAmmoIndexUnknown; // 1588 (runtime variable)
		char __pad002[3]; // padding?
		int iClipIndex; // 1592 (runtime variable)
		char iClipIndexUnknown; // 1596 (runtime variable)
		char __pad003[3]; // padding?
		int iMaxAmmo; // 1600
		int iMinAmmoReq; // 1604
		int iClipSize; // 1608
		int shotCount; // 1612
		int iSharedAmmoCapIndex; // 1616
		int iSharedAmmoCap; // 1620
		int damage; // 1624
		int playerDamage; // 1628
		int iMeleeDamage; // 1632
		int iDamageType; // 1636
		StateTimers stateTimers; // 1640
		StateTimers akimboStateTimers; // 1940
		float autoAimRange; // 2240
		float aimAssistRange; // 2244
		float aimAssistRangeAds; // 2248
		float aimPadding; // 2252
		float enemyCrosshairRange; // 2256 
		float moveSpeedScale; // 2260
		float adsMoveSpeedScale; // 2264
		float sprintDurationScale; // 2268
		float fAdsZoomFov; // 2272
		float fAdsZoomInFrac; // 2276
		float fAdsZoomOutFrac; // 2280
		float fAdsSceneBlur; // 2284 (1401FC630) : float
		float fU_007; // 2288 (1400CF870) : float (related to scene blur)
		float xU_008; // 2292 X
		ADSOverlay overlay; // 2296
		WeapOverlayInteface_t overlayInterface; // 2352
		float fAdsBobFactor; // 2356
		float fAdsViewBobMult; // 2360
		float fHipSpreadStandMin; // 2364
		float fHipSpreadDuckedMin; // 2368
		float fHipSpreadProneMin; // 2372
		float fHipSpreadStandMax; // 2376
		float xU_009; // 2380 X
		float xU_010; // 2384 X
		float fHipSpreadDuckedMax; // 2388
		float fHipSpreadProneMax; // 2392
		float fHipSpreadDecayRate; // 2396
		float fHipSpreadFireAdd; // 2400
		float fHipSpreadTurnAdd; // 2404
		float fHipSpreadMoveAdd; // 2408
		float fHipSpreadDuckedDecay; // 2412
		float fHipSpreadProneDecay; // 2416
		float fHipReticleSidePos; // 2420
		float fAdsIdleAmount; // 2424
		float fHipIdleAmount; // 2428
		float fAdsIdleSpeed; // 2432
		float fHipIdleSpeed; // 2436f
		float fIdleCrouchFactor; // 2440
		float fIdleProneFactor; // 2444
		float fGunMaxPitch; // 2448
		float fGunMaxYaw; // 2452
		float adsIdleLerpStartTime; // 2456
		float adsIdleLerpTime; // 2460
		int adsTransInTime; // 2464
		int xU_011; // 2468 X
		int adsTransOutTime; // 2472
		float xU_012; // 2476 X
		float swayMaxAngle; // 2480
		float swayLerpSpeed; // 2484
		float swayPitchScale; // 2488
		float swayYawScale; // 2492
		float swayVertScale; // 2496
		float swayHorizScale; // 2500
		float swayShellShockScale; // 2504
		float adsSwayMaxAngle; // 2508
		float adsSwayLerpSpeed; // 2512
		float adsSwayPitchScale; // 2516
		float adsSwayYawScale; // 2520
		float adsSwayHorizScale; // 2524
		float adsSwayVertScale; // 2528
		float adsViewErrorMin; // 2532
		float adsViewErrorMax; // 2536
		float adsFireAnimFrac; // 2540
		float dualWieldViewModelOffset; // 2544
		float fScopeDriftDelay; // 2548
		float fScopeDriftLerpInTime; // 2552
		float fScopeDriftSteadyTime; // 2556
		float fScopeDriftLerpOutTime; // 2560
		float fScopeDriftSteadyFactor; // 2564
		float fScopeDriftUnsteadyFactor; // 2568
		float bobVerticalFactor; // 2572
		float bobHorizontalFactor; // 2576
		float bobViewVerticalFactor; // 2580
		float bobViewHorizontalFactor; // 2584
		float stationaryZoomFov; // 2588
		float stationaryZoomDelay; // 2592
		float stationaryZoomLerpInTime; // 2596
		float stationaryZoomLerpOutTime; // 2600
		float adsDofStart; // 2604
		float adsDofEnd; // 2608
		float xU_020; // 2612 X
		Material* killIcon; // 2616
		Material* dpadIcon; // 2624
		Material* hudProximityWarningIcon; // 2632
		weaponIconRatioType_t killIconRatio; // 2640
		weaponIconRatioType_t dpadIconRatio; // 2644
		int fireAnimLength; // 2648
		int fireAnimLengthAkimbo; // 2652
		int inspectAnimTime; // 2656
		int iReloadAmmoAdd; // 2660
		int iReloadStartAdd; // 2664
		int ammoDropStockMin; // 2668
		int ammoDropStockMax; // 2672
		int ammoDropClipPercentMin; // 2676
		int ammoDropClipPercentMax; // 2680
		int iExplosionRadius; // 2684
		int iExplosionRadiusMin; // 2688
		int iExplosionInnerDamage; // 2692
		int iExplosionOuterDamage; // 2696
		float damageConeAngle; // 2700
		float bulletExplDmgMult; // 2704
		float bulletExplRadiusMult; // 2708
		int iProjectileSpeed; // 2712
		int iProjectileSpeedUp; // 2716
		int iProjectileSpeedForward; // 2720
		int iProjectileActivateDist; // 2724
		float projLifetime; // 2728
		float timeToAccelerate; // 2732
		float projectileCurvature; // 2736
		float xU_021; // 2740 X
		const char* projectileName; // 2744
		XModel* projectileModel; // 2752
		FxEffectDef* projExplosionEffect; // 2760
		FxEffectDef* projDudEffect; // 2768
		snd_alias_list_t* projExplosionSound; // 2776
		snd_alias_list_t* projDudSound; // 2784
		weapProjExposion_t projExplosion; // 2792
		WeapStickinessType stickiness; // 2796
		float lowAmmoWarningThreshold; // 2800
		float ricochetChance; // 2804
		int riotShieldHealth; // 2808
		float riotShieldDamageMult; // 2812
		float* parallelBounce; // 2816 (53 floats)
		float* perpendicularBounce; // 2824 (53 floats)
		FxEffectDef* projTrailEffect; // 2832
		FxEffectDef* projBeaconEffect; // 2840
		float vProjectileColor[3]; // 2848 2852 2856
		guidedMissileType_t guidedMissileType; // 2860
		float maxSteeringAccel; // 2864
		int projIgnitionDelay; // 2868
		FxEffectDef* projIgnitionEffect; // 2872
		snd_alias_list_t* projIgnitionSound; // 2880
		float fAdsAimPitch; // 2888
		float fAdsCrosshairInFrac; // 2892
		float fAdsCrosshairOutFrac; // 2896
		int adsGunKickReducedKickBullets; // 2900
		float adsGunKickReducedKickPercent; // 2904
		float fAdsGunKickPitchMin; // 2908 (BG_WeaponFireRecoil) : float
		float fAdsGunKickPitchMax; // 2912 (BG_WeaponFireRecoil) : float
		float fAdsGunKickYawMin; // 2916 (BG_WeaponFireRecoil) : float
		float fAdsGunKickYawMax; // 2920 (BG_WeaponFireRecoil) : float
		float fAdsGunKickMagMin; // 2924 (BG_WeaponFireRecoil) : float
		float fAdsGunKickAccel; // 2928 (BG_CalculateWeaponMovement_Recoil) : float
		float fAdsGunKickSpeedMax; // 2932 (BG_CalculateWeaponMovement_Recoil) : float
		float fAdsGunKickSpeedDecay; // 2936 (BG_CalculateWeaponMovement_Recoil) : float
		float fAdsGunKickStaticDecay; // 2940 (BG_CalculateWeaponMovement_Recoil) : float
		float fAdsViewKickPitchMin; // 2944 (BG_WeaponFireRecoil) : float
		float fAdsViewKickPitchMax; // 2948 (BG_WeaponFireRecoil) : float
		float fAdsViewKickYawMin; // 2952 (BG_WeaponFireRecoil) : float
		float fAdsViewKickYawMax; // 2956 (BG_WeaponFireRecoil) : float
		float fAdsViewKickMagMin; // 2960 (BG_WeaponFireRecoil) : float
		float fAdsViewKickCenterSpeed; // 2964
		float fAdsViewScatterMin; // 2968 X
		float fAdsViewScatterMax; // 2972 X
		float fAdsSpread; // 2976
		int hipGunKickReducedKickBullets; // 2980
		float hipGunKickReducedKickPercent; // 2984 (BG_WeaponFireRecoil) : float
		float fHipGunKickPitchMin; // 2988 (BG_WeaponFireRecoil) : float
		float fHipGunKickPitchMax; // 2992 (BG_WeaponFireRecoil) : float
		float fHipGunKickYawMin; // 2996 (BG_WeaponFireRecoil) : float
		float fHipGunKickYawMax; // 3000 (BG_WeaponFireRecoil) : float
		float fHipGunKickMagMin; // 3004 (BG_WeaponFireRecoil) : float
		float fHipGunKickAccel; // 3008 (BG_CalculateWeaponMovement_Recoil) : float
		float fHipGunKickSpeedMax; // 3012 (BG_CalculateWeaponMovement_Recoil) : float
		float fHipGunKickSpeedDecay; // 3016 (BG_CalculateWeaponMovement_Recoil) : float
		float fHipGunKickStaticDecay; // 3020 (BG_CalculateWeaponMovement_Recoil) : float
		float fHipViewKickPitchMin; // 3024 (BG_WeaponFireRecoil) : float
		float fHipViewKickPitchMax; // 3028 (BG_WeaponFireRecoil) : float
		float fHipViewKickYawMin; // 3032 (BG_WeaponFireRecoil) : float
		float fHipViewKickYawMax; // 3036 (BG_WeaponFireRecoil) : float
		float fHipViewKickMagMin; // 3040 (BG_WeaponFireRecoil) : float
		float fHipViewKickCenterSpeed; // 3044
		float fHipViewScatterMin; // 3048 //*
		float fHipViewScatterMax; // 3052 //*
		float xU_043; // 3056 //*
		int adsReloadTransTime; // 3060
		float fightDist; // 3064
		float maxDist; // 3068 (Bot_GetAdjustedMaxRange)(Bot_Weap_IsRanged)
		const char* accuracyGraphName[2]; // 3072
		vec2_t* accuracyGraphKnots[2]; // 3088
		vec2_t* originalAccuracyGraphKnots[2]; // 3104
		short accuracyGraphKnotCount[2]; // 3120
		int iPositionReloadTransTime; // 3124 X
		float leftArc; // 3128
		float rightArc; // 3132
		float topArc; // 3136
		float bottomArc; // 3140
		float accuracy; // 3144
		float aiSpread; // 3148
		float playerSpread; // 3152
		float minTurnSpeed[2]; //3156
		float maxTurnSpeed[2]; // 3164
		float pitchConvergenceTime; // 3172
		float yawConvergenceTime; // 3176
		float suppressTime; // 3180
		float maxRange; // 3184
		float fAnimHorRotateInc; // 3188
		float fPlayerPositionDist; // 3192
		unsigned int iUseHintStringIndex; // 3196 (runtime variable)
		unsigned int dropHintStringIndex; // 3200 (runtime variable)
		float horizViewJitter; // 3204
		float vertViewJitter; // 3208
		float scanSpeed; // 3212
		float scanAccel; // 3216
		int scanPauseTime; // 3220
		const char* szScript; // 3224
		int minDamage; // 3232
		int midDamage; // 3236
		int minPlayerDamage; // 3240
		int midPlayerDamage; // 3244
		float fMaxDamageRange; // 3248
		float fMinDamageRange; // 3252
		int iU_045; // 3256 X
		int iU_046; // 3260 X
		int iU_047; // 3264 X
		int iU_048; // 3268 X
		float fU_049; // 3272 X
		float fU_050; // 3276 X
		float destabilizationRateTime; // 3280
		float destabilizationCurvatureMax; // 3284
		int destabilizeDistance; // 3288
		float turretADSTime; // 3292
		float turretFov; // 3296 X
		float turretFovADS; // 3300 X
		float turretScopeZoomRate; // 3304 X
		float turretScopeZoomMin; // 3308 X
		float turretScopeZoomMax; // 3312 X
		float xU_056; // 3316 X
		float xU_057; // 3320 X
		float xU_058; // 3324 X
		float xU_059; // 3328 X
		float turretBarrelSpinSpeed; // 3332
		float turretBarrelSpinUpTime; // 3336
		float turretBarrelSpinDownTime; // 3340 X
		float missileConeSoundRadiusAtTop; // 3344 X
		float missileConeSoundRadiusAtBase; // 3348 X
		float missileConeSoundHeight; // 3352 X
		float missileConeSoundOriginOffset; // 3356 X
		float missileConeSoundVolumescaleAtCore; // 3360 X
		float missileConeSoundVolumescaleAtEdge; // 3364 X
		float missileConeSoundVolumescaleCoreSize; // 3368 X
		float missileConeSoundPitchAtTop; // 3372 X
		float missileConeSoundPitchAtBottom; // 3376 X
		float missileConeSoundPitchTopSize; // 3380 X
		float missileConeSoundPitchBottomSize; // 3384 X
		float missileConeSoundCrossfadeTopSize; // 3388 X
		float missileConeSoundCrossfadeBottomSize; // 3392 X
		float aim_automelee_lerp; // 3396
		float aim_automelee_range; // 3400
		float aim_automelee_region_height; // 3404
		float aim_automelee_region_width; // 3408
		float player_meleeHeight; // 3412
		float player_meleeRange; // 3416
		float player_meleeWidth; // 3420
		float signatureFireTime; // 3424
		int signatureNumBullets; // 3428
		weapFireTimeInterpolation_t fireTimeInterpolationType; // 3432
		int xU_075; // 3436 X
		int iAmmoUsedPerShot; // 3440 (Bot_Weap_WeaponUsesAmmo)
		int xU_076; // 3444 X
		int xU_077; // 3448 X
		int xU_078; // 3452 X
		int iU_079; // 3456 // int numBulletTags (BG_ShowHideTagsBasedOnAltMode)
		int iU_080; // 3460 // int tagForAmmo (1400C77D0)
		scr_string_t stowTag; // 3464
		bool bU_081; // 3468 X
		bool unknownReticleBooleanValue1; // 3469 (CG_DrawCrosshair)
		bool unknownReticleBooleanValue2; // 3470 (CG_DrawCrosshair)
		bool turretADSEnabled; // 3471 X
		bool knifeAttachTagLeft; // 3472
		bool knifeAlwaysAttached; // 3473
		bool meleeOverrideValues; // 3474
		bool bU_083; // 3475 X
		bool bU_084; // 3476 X
		bool sharedAmmo; // 3477
		bool lockonSupported; // 3478
		bool requireLockonToFire; // 3479
		bool isAirburstWeapon; // 3480 X
		bool bigExplosion; // 3481 X
		bool noAdsWhenMagEmpty; // 3482
		bool avoidDropCleanup; // 3483
		bool inheritsPerks; // 3484
		bool crosshairColorChange; // 3485
		bool bRifleBullet; // 3486
		bool armorPiercing; // 3487
		bool bBoltAction; // 3488
		bool aimDownSight; // 3489
		bool canHoldBreath; // 3490
		bool meleeOnly; // 3491
		bool bU_085; // 3492 bool isMeleeAnimDelayed;? (0x14009FDC0)(1401F2BC0)
		bool bU_086; // 3493 X bool oldWeaponBot;?
		bool canVariableZoom; // 3494
		bool bRechamberWhileAds; // 3495
		bool bBulletExplosiveDamage; // 3496
		bool bCookOffHold; // 3497
		bool reticleSpin45; // 3498 X
		bool reticleSideEnabled; // 3499
		bool bClipOnly; // 3500
		bool noAmmoPickup; // 3501
		bool disableSwitchToWhenEmpty; // 3502
		bool bU_088; // 3503 (14017E520) bool hiddenAmmo;?
		bool hasMotionTracker; // 3504
		bool bU_089; // 3505 X
		bool noDualWield; // 3506
		bool flipKillIcon; // 3507
		bool actionSlotShowAmmo; // 3508
		bool bNoPartialReload; // 3509
		bool bSegmentedReload; // 3510
		bool bMultipleReload; // 3511
		bool blocksProne; // 3512
		bool silenced; // 3513
		bool isRollingGrenade; // 3514
		bool projExplosionEffectForceNormalUp; // 3515
		bool projExplosionEffectInheritParentDirection; // 3516
		bool bProjImpactExplode; // 3517
		bool bProjTrajectoryEvents; // 3518 X
		bool bProjWhizByEnabled; // 3519 X
		bool stickToPlayers; // 3520 X
		bool stickToVehicles; // 3521 X
		bool stickToTurrets; // 3522 X
		bool thrownSideways; // 3523 X
		bool hasDetonatorEmptyThrow; // 3524
		bool hasDetonatorDoubleTap; // 3525
		bool disableFiring; // 3526
		bool timedDetonation; // 3527
		bool bU_090; // 3528 (G_FireGrenade)(CheckCrumpleMissile) bool usesGrenadeTimer?
		bool bU_091; // 3529 (G_FireRocket) bool usesRocketTimer?
		bool rotate; // 3530
		bool holdButtonToThrow; // 3531 X
		bool freezeMovementWhenFiring; // 3532
		bool thermalScope; // 3533
		bool thermalToggle; // 3534
		bool outlineEnemies; // 3535
		bool altModeSameWeapon; // 3536
		bool turretBarrelSpinEnabled; // 3537
		bool missileConeSoundEnabled; // 3538 X
		bool missileConeSoundPitchshiftEnabled; // 3539 X
		bool missileConeSoundCrossfadeEnabled; // 3540 X
		bool offhandHoldIsCancelable; // 3541
		bool doNotAllowAttachmentsToOverrideSpread; // 3542
		bool useFastReloadAnims; // 3543 (140202800)
		bool dualMagReloadSupported; // 3544
		bool reloadStopsAlt; // 3545 X
		bool bU_092; // 3546 X
		bool alwaysShatterGlassOnImpact; // 3547
		bool oldWeapon; // 3548
		bool bU_093; // 3549 bool isC4;? (BulletRicochet)(PM_Weapon_OffHandPrepare)
		bool bU_094; // 3550 (BG_WeaponFireRecoil)(Missile_Impact)
		bool xU_095; // 3551 X
		bool hasCounterSilencer; // 3552 (BG_HasCounterSilencer)
		bool xU_097; // 3553 X
		bool xU_098; // 3554 X
		bool disableVariableAutosimRate; // 3555 (BG_GetDisableVariableAutosimRate)
		bool bU_100; // 3556 (CG_Missile)
		bool bU_101; // 3557 (CG_Missile)
		bool bU_102; // 3558 (CG_Missile)
		bool bU_103; // 3559 (CG_Missile)
		bool bU_104; // 3560 X
		bool cloakedWeapon; // 3561 (BG_IsWeaponCloaked)
		bool adsHideWeapon; // 3562 (0x1401fa7aa)
		bool adsHideHands; // 3563 (0x1401fa78a)
		bool bU_108; // 3564 X
		bool adsBlurSceneEnabled; // 3565 (BG_GetADSSceneBlur)
		bool usesSniperScope; // 3566 (BG_UsingSniperScope)
		bool bU_111; // 3567 (140499130) (14049CE70) (14049B890) (14049B680)
		bool bU_112; // 3568 X
		bool bU_113; // 3569 X
		bool bU_114; // 3570 (BG_ShowHideTagsBasedOnAltMode)
		bool bU_115; // 3571 (BG_ShowHideTagsBasedOnAltMode)
		float adsDofPhysicalFStop; // 3572 (BG_ADSDOFPhysicalFStop)
		float adsDofPhysicalFocusDistance; // 3576 (BG_ADSDOFPhysicalFocusDistance)
		float autosimSpeedScalar; // 3580 (BG_GetAutosimSpeedScalar)
		float explosionReactiveMotionParts[5]; // 3584 (BG_GetExplosionReactiveMotionParams)
		char __pad_unknown[12]; // 3604
		//1400C7650
		// size: 3616
	}; static_assert(sizeof(WeaponDef) == 0xE20);

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
		WeaponDef* weapon;
		FxEffectDef* fx;
		RawFile* rawfile;
		ScriptFile* scriptfile;
		StringTable* stringTable;
		StructuredDataDefSet* structuredDataDefSet;
		NetConstStrings* netConstStrings;
		TracerDef* tracerDef;
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

	typedef std::uint32_t GfxBlendStateBits[3];

	struct XGfxGlobals
	{
		unsigned int depthStencilStateCount;
		unsigned int blendStateCount;
		std::uint64_t* depthStencilStateBits;
		GfxBlendStateBits* blendStateBits;
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