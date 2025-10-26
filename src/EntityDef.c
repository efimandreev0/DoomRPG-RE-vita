
#include <SDL.h>
#include <stdio.h>
#include <string.h>

#include "DoomRPG.h"
#include "EntityDef.h"
#include "SDL_Video.h"

EntityDefManager_t* EntityDef_init(EntityDefManager_t* entityDef, DoomRPG_t* doomRpg)
{
	printf("EntityDef_init\n");

	if (entityDef == NULL)
	{
		entityDef = SDL_malloc(sizeof(EntityDefManager_t));
		if (entityDef == NULL) {
			return NULL;
		}
	}
	SDL_memset(entityDef, 0, sizeof(EntityDefManager_t));

	entityDef->list = NULL;
	entityDef->doomRpg = doomRpg;
	entityDef->numDefs = 0;

	return entityDef;
}

void EntityDef_free(EntityDefManager_t* entityDef, boolean freePtr)
{
	SDL_free(entityDef->list);
	if (freePtr) {
		SDL_free(entityDef);
	}
}

EntityDef_t* EntityDef_find(EntityDefManager_t* entDef, byte b, byte b2)
{
	for (int i = 0; i < entDef->numDefs; i++) {
		if (entDef->list[i].eType == b && entDef->list[i].eSubType == b2) {
			return &entDef->list[i];
		}
	}
	return NULL;
}

EntityDef_t* EntityDef_lookup(EntityDefManager_t* entDef, int i)
{
	int length = entDef->numDefs;
	for (int j = 0; j < length; j++) {
		if (entDef->list[j].tileIndex == i) {
			return &entDef->list[j];
		}
	}
	return NULL;
}

void readEntityNames(EntityDefManager_t *entityDef, const char *txtName)
{
    FILE *fp = fopen(txtName, "r");
    if (!fp) {
        return;
    }

    char line[128];
    size_t i = 0;
    while (i < entityDef->numDefs && fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';

        strncpy(entityDef->list[i].name, line, sizeof(entityDef->list[i].name) - 1);
        entityDef->list[i].name[sizeof(entityDef->list[i].name) - 1] = '\0';

        i++;
    }

    fclose(fp);
}
int EntityDef_startup(EntityDefManager_t* entityDef)
{
	byte *fData;
	EntityDef_t* list;
	int dataPos, i;

	fData = DoomRPG_fileOpenRead(entityDef->doomRpg, "/entities.db");
	dataPos = 0;
	entityDef->numDefs = DoomRPG_shortAtNext(fData, &dataPos);

	entityDef->list = SDL_malloc(entityDef->numDefs * sizeof(EntityDef_t));
	if (entityDef->list == NULL) {
		DoomRPG_Error("EntityDef_startup: Insufficient memory for allocation");
		return 0;
	}

	for(i = 0; i < entityDef->numDefs; i++)
	{
		list = &entityDef->list[i];
		list->tileIndex = DoomRPG_shortAtNext(fData, &dataPos);
		list->eType = DoomRPG_byteAtNext(fData, &dataPos);
		list->eSubType = DoomRPG_byteAtNext(fData, &dataPos);
		list->parm = DoomRPG_intAtNext(fData, &dataPos);
		strncpy(list->name, fData + dataPos, sizeof(list->name));
		dataPos += sizeof(list->name);
	}

	const char* base_path = "ux0:data/DoomRPG/";
	char full_path[128];
	snprintf(full_path, sizeof(full_path), "%s%s/%s", base_path, entityDef->doomRpg->lang, "entities.txt");
	if (!file_exists(full_path)) {
		snprintf(full_path, sizeof(full_path), "%s%s", base_path, "en/entities.txt");
	}
	if (file_exists(full_path)) {
		readEntityNames(entityDef, full_path);
	}
	SDL_free(fData);

	/*for (i = 0; i < entityDef->numDefs; i++)
	{
		list = &entityDef->list[i];
		printf("\nList[%d]............................\n", i);
		printf("tileIndex %d\n",list->tileIndex);
		printf("eType %d\n", list->eType);
		printf("eSubType %d\n", list->eSubType);
		printf("parm %d\n", list->parm);
		printf("name %s\n", list->name);
	}*/

	return 1;
}