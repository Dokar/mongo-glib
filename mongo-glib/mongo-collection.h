/* mongo-collection.h
 *
 * Copyright (C) 2012 Christian Hergert <chris@dronelabs.com>
 *
 * This file is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined (MONGO_INSIDE) && !defined (MONGO_COMPILATION)
#error "Only <mongo-glib/mongo-glib.h> can be included directly."
#endif

#ifndef MONGO_COLLECTION_H
#define MONGO_COLLECTION_H

#include <glib-object.h>
#include <gio/gio.h>

#include "mongo-bson.h"
#include "mongo-cursor.h"
#include "mongo-protocol.h"

G_BEGIN_DECLS

#define MONGO_TYPE_COLLECTION            (mongo_collection_get_type())
#define MONGO_COLLECTION(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), MONGO_TYPE_COLLECTION, MongoCollection))
#define MONGO_COLLECTION_CONST(obj)      (G_TYPE_CHECK_INSTANCE_CAST ((obj), MONGO_TYPE_COLLECTION, MongoCollection const))
#define MONGO_COLLECTION_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  MONGO_TYPE_COLLECTION, MongoCollectionClass))
#define MONGO_IS_COLLECTION(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MONGO_TYPE_COLLECTION))
#define MONGO_IS_COLLECTION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  MONGO_TYPE_COLLECTION))
#define MONGO_COLLECTION_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  MONGO_TYPE_COLLECTION, MongoCollectionClass))

typedef struct _MongoCollection        MongoCollection;
typedef struct _MongoCollectionClass   MongoCollectionClass;
typedef struct _MongoCollectionPrivate MongoCollectionPrivate;

struct _MongoCollection
{
   GObject parent;

   /*< private >*/
   MongoCollectionPrivate *priv;
};

struct _MongoCollectionClass
{
   GObjectClass parent_class;
};

GType        mongo_collection_get_type      (void) G_GNUC_CONST;
MongoCursor *mongo_collection_find          (MongoCollection      *collection,
                                             const MongoBson      *query,
                                             const MongoBson      *field_selector,
                                             guint                 offset,
                                             guint                 limit,
                                             MongoQueryFlags       flags);
void         mongo_collection_drop_async    (MongoCollection      *collection,
                                             GCancellable         *cancellable,
                                             GAsyncReadyCallback   callback,
                                             gpointer              user_data);
gboolean     mongo_collection_drop_finish   (MongoCollection      *collection,
                                             GAsyncResult         *result,
                                             GError              **error);
void         mongo_collection_insert_async  (MongoCollection      *collection,
                                             MongoBson           **documents,
                                             gsize                 n_documents,
                                             MongoInsertFlags      flags,
                                             GCancellable         *cancellable,
                                             GAsyncReadyCallback   callback,
                                             gpointer              user_data);
gboolean     mongo_collection_insert_finish (MongoCollection      *collection,
                                             GAsyncResult         *result,
                                             GError              **error);
void         mongo_collection_remove_async  (MongoCollection      *collection,
                                             const MongoBson      *selector,
                                             MongoDeleteFlags      flags,
                                             GCancellable         *cancellable,
                                             GAsyncReadyCallback   callback,
                                             gpointer              user_data);
gboolean     mongo_collection_remove_finish (MongoCollection      *collection,
                                             GAsyncResult         *result,
                                             GError              **error);
void         mongo_collection_update_async  (MongoCollection      *collection,
                                             const MongoBson      *selector,
                                             const MongoBson      *update,
                                             MongoUpdateFlags      flags,
                                             GCancellable         *cancellable,
                                             GAsyncReadyCallback   callback,
                                             gpointer              user_data);
gboolean     mongo_collection_update_finish (MongoCollection      *collection,
                                             GAsyncResult         *result,
                                             GError              **error);


G_END_DECLS

#endif /* MONGO_COLLECTION_H */
