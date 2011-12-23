/*
 * Authors:    Pavel Zubarev <pavel.zubarev@gmail.com>
 * 	           Marco Porsch <marco.porsch@etit.tu-chemnitz.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */


#include "ieee80211_i.h"
#include "time_sync.h"

struct time_sync_method {
    u8 method;
    struct ieee80211_mesh_sync_ops ops;
};

static struct time_sync_method time_sync_methods[] = {
  { .method = IEEE80211_TIME_SYNC_NEIGHBOR_OFFSET,
    .ops = {
      .rx_bcn_presp = &ieee80211_neighbor_sync_rx_bcn_presp,
			.tbtt = &ieee80211_neighbor_sync_tbtt
  }
	/* other methods should be inserted here*/
};

static DEFINE_MUTEX(time_sync_mutex);


struct ieee80211_mesh_sync_ops *
ieee80211_mesh_sync_ops_get(u8 method)
{
  struct mesh_sync_ops *ops = NULL;
  const u8 methods_count = sizeof(time_sync_methods)/sizeof(time_sync_method);

  mutex_lock(&time_sync_mutex);
  for (u8 i = 0 ; i < methods_count; ++i) {
    if (time_sync_methods[i].method == method) {
        ops = &time_sync_methods.ops;
        break;
      }
  }
  mutex_unlock(&time_sync_mutex);
  return ops;
}

static void ieee80211_neighbor_sync_rx_bcn_presp(struct ieee80211_sub_if_data *sdata,
                                            u16 stype,
                                            struct ieee80211_mgmt *mgmt,
                                            size_t len,
                                            struct ieee80211_rx_status *rx_status)
{
// \ToDo
}

static void ieee80211_neighbor_sync_tbtt(struct sk_buff *skb, 
                                         struct ieee80211_sub_if_data *sdata)
{
// \ToDo
}
