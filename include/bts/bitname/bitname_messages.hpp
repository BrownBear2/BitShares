#pragma once
#include <bts/bitname/bitname_block.hpp>

namespace bts { namespace bitname { 

  /**
   *  Defines the message codes that are broadcast on the name_proto
   *  channel.
   */
  enum message_type 
  {
     name_inv_msg,
     block_inv_msg,
     get_name_inv_msg,
     get_headers_msg,
     get_block_msg,
     get_block_index_msg,
     get_name_header_msg,
     name_header_msg,
     block_msg,
     block_index_msg,
     headers_msg
  };

  struct name_inv_message
  {
    static const message_type        type;
    std::vector<short_name_id_type>  name_trxs;
  };

  struct block_inv_message
  {
    static const message_type type;
    std::vector<name_id_type>  block_ids;
  };

  struct get_name_inv_message
  {
    static const message_type type;
  };

  struct get_headers_message
  {
    static const message_type type;
    std::vector<name_id_type>  locator_hashes;
  };

  struct get_block_message
  {
    static const message_type type;
    get_block_message( const name_id_type& id )
    :block_id(id){}
    get_block_message(){}

    name_id_type block_id;
  };
  struct get_block_index_message
  {
    static const message_type type;
    get_block_index_message( const name_id_type& id )
    :block_id(id){}
    get_block_index_message(){}

    name_id_type block_id;
  };

  struct get_name_header_message
  {
    static const message_type type;
    get_name_header_message(short_name_id_type trx_id = 0)
    :name_trx_id(trx_id){}

    short_name_id_type name_trx_id;
  };

  struct name_header_message
  {
    static const message_type type;
    name_header_message(){}
    name_header_message( const name_header& cpy )
    :trx(cpy){}

    name_header           trx; 
  };

  struct block_message
  {
    static const message_type type;
    block_message(){}
    block_message( name_block&& blk )
    :block( std::move(blk) ){}

    name_block block;
  };

  struct block_index_message
  {
    static const message_type type;
    block_index_message(){}
    block_index_message( const name_block_index& nbi )
    :index(nbi){}
    name_block_index index; 
  };

  struct headers_message
  {
    static const message_type type;
    headers_message()
    :first_block_num(0),head_block_num(0){}

    uint32_t                   first_block_num;
    name_header                first;
    std::vector<name_trx>      headers;
    // in the event that there are more than 2000 header_ids,
    // this will tell the client there are more and what the
    // current head is, so they can request more
    uint32_t                   head_block_num;
    name_id_type               head_block_id;
  };


} } // bts::bitname


FC_REFLECT_ENUM( bts::bitname::message_type,
    (name_inv_msg)
    (block_inv_msg)
    (get_name_inv_msg)
    (get_headers_msg)
    (get_block_msg)
    (get_block_index_msg)
    (get_name_header_msg)
    (name_header_msg)
    (block_msg)
    (block_index_msg)
    (headers_msg)
)

#include <fc/reflect/reflect.hpp>
FC_REFLECT( bts::bitname::name_inv_message, (name_trxs))
FC_REFLECT( bts::bitname::block_inv_message, (block_ids))
FC_REFLECT( bts::bitname::get_name_inv_message, BOOST_PP_SEQ_NIL )
FC_REFLECT( bts::bitname::get_headers_message, (locator_hashes) )
FC_REFLECT( bts::bitname::get_block_message, (block_id))
FC_REFLECT( bts::bitname::get_block_index_message, (block_id))
FC_REFLECT( bts::bitname::get_name_header_message, (name_trx_id))
FC_REFLECT( bts::bitname::name_header_message, (trx))
FC_REFLECT( bts::bitname::block_message,(block) )
FC_REFLECT( bts::bitname::block_index_message,(index) )
FC_REFLECT( bts::bitname::headers_message, (first_block_num)(first)(headers)(head_block_num)(head_block_id))

