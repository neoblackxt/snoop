#include <SnoopIcmp>

#include <VDebugNew>

// ----------------------------------------------------------------------------
// SnoopIcmp
// ----------------------------------------------------------------------------
bool SnoopIcmp::isData(IP_HDR* ipHdr, ICMP_HDR* icmpHdr, uint8_t** icmpData, int* icmpDataLen)
{
  Q_UNUSED(ipHdr)
  Q_UNUSED(icmpHdr)
  Q_UNUSED(icmpData)
  Q_UNUSED(icmpDataLen)
  return false; // gilgil temp 2009.09.08
  /*
  int _icmpDataLen;

  if (icmpData != NULL)
    *icmpData = (uint8_t*)(icmpHdr) + sizeof(ICMP_HDR);
    icmpHdr->dun.
  _icmpDataLen = ntohs(icmpHdr-> uh_ulen) - sizeof(ICMP_HDR);
  if (icmpDataLen != NULL)
    *icmpDataLen = _icmpDataLen;
  return _icmpDataLen > 0;
  */
}

//
// All icmpHdr field except icmpHdr.uh_sum
// Added ipHdr.ip_src, ipHdr.ip_dst, icmpHdrDataLen and IPPROTO_ICMP
//
uint16_t SnoopIcmp::checksum(IP_HDR* ipHdr, ICMP_HDR* icmpHdr)
{
  Q_UNUSED(ipHdr)
  Q_UNUSED(icmpHdr)
  return 0;

  /* gilgil temp 2009.09.08
  int i;
  int icmpHdrDataLen;
  uint16_t *p;
  uint32_t src, dst;
  uint32_t sum;

  icmpHdrDataLen = ntohs(icmpHdr->uh_ulen);
  sum = 0;

  // Add icmpHdr & data buffer as array of uint16_t
  p = (uint16_t*)icmpHdr;
  for (i = 0; i < icmpHdrDataLen / 2; i++)
  {
    sum += htons(*p);
    p++;
  }

  // If length is odd, add Last Data
  if ((icmpHdrDataLen / 2) * 2 != icmpHdrDataLen)
    sum += (htons(*p) & 0xFF00);

  // Decrease checksum from sum
  sum -= ntohs(icmpHdr->uh_sum);

  // Add src address
  src = ntohl(ipHdr->ip_src);
  sum += ((src & 0xFFFF0000) >> 16) + (src & 0x0000FFFF);

  // Add dst address
  dst = ntohl(ipHdr->ip_dst);
  sum += ((dst & 0xFFFF0000) >> 16) + (dst & 0x0000FFFF);

  // Add extra onformation
  sum += (uint32_t)icmpHdrDataLen + IPPROTO_ICMP;

  // Recalculate sum
  while ((sum >> 16) > 0)
    sum = (sum & 0xFFFF) + (sum >> 16);
  sum = ~sum;

  return (uint16_t)sum;
  */
}

bool SnoopIcmp::parse(SnoopPacket* packet)
{
  if (!SnoopIp::isIcmp(packet->ipHdr, &packet->icmpHdr)) return false;
  packet->proto = IPPROTO_ICMP;
  return true;
}

bool SnoopIcmp::parseAll(SnoopPacket* packet)
{
  if (!SnoopIp::parseAll(packet)) return false;
  return parse(packet);
}
