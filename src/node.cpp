/*
BSD 3-Clause License

Copyright (c) 2020, The Regents of the University of Minnesota

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <vector>
#include <sstream>
#include "node.h"
#include "pdnsim/pdnsim.h"
using namespace pdnsim;

using namespace std;

//! Get the layer number of the node
/*
 * \return Layer number of the node
 * */
int Node::GetLayerNum()
{
  return m_layer;
}


//! Set the layer number of the node
/*
 \param t_layer Layer number
*/
void Node::SetLayerNum(int t_layer)
{
  m_layer = t_layer;
}


//! Get the location of the node
/*
 * \return NodeLoc which is x and y index
 * */
NodeLoc Node::GetLoc()
{
  return m_loc;
}


//! Set the location of the node using x and y coordinates
/*
 * \param t_x x index
 * \param t_y y index
 * */
void Node::SetLoc(int t_x, int t_y)
{
  m_loc = make_pair(t_x, t_y);
}


//! Set the location of the node using x,y and layer information
/*
 * \param t_x x index
 * \param t_y y index
 * \param t_l Layer number
 * */
void Node::SetLoc(int t_x, int t_y, int t_l)
{
  SetLayerNum(t_l);
  SetLoc(t_x, t_y);
}

//! Get location of the node in G matrix
/*
 * \return Location in G matrix
 */
NodeIdx Node::GetGLoc()
{
  return m_node_loc;
}

//! Set location of the node in G matrix
/*
 * \param t_loc Location in the G matrix
 */
void Node::SetGLoc(NodeIdx t_loc)
{
  m_node_loc = t_loc;
}

//! Function to print node details
void Node::Print()
{
  stringstream s;
  s << "Node: " << m_node_loc << endl
  << "    Location: Layer " << m_layer << ", x " << m_loc.first << ", y "<<endl
  << m_loc.second << endl
  << "    Current: " << m_current_src << endl
  << "    Voltage: " << m_voltage << endl
  << "    Has connection: " << m_connected <<endl
  << "    Has instances:  " << m_has_instances <<endl;
  PdnsimLogger(INFO, -1, s.str());
}

//! Function to set the current value at a particular node
/*
 * \param t_current Current magnitude
 */
void Node::SetCurrent(double t_current)
{
  m_current_src = t_current;
}

//! Function to get the value of current at a node
double Node::GetCurrent()
{
  return m_current_src;
}

//! Function to add the current source 
/*
 * \param t_current Value of current source
 */
void Node::AddCurrentSrc(double t_current)
{
  double node_cur = GetCurrent();
  SetCurrent(node_cur + t_current);
}

//! Function to set the value of the voltage source
/*
 * \param t_voltage Voltage source magnitude
 * */
void Node::SetVoltage(double t_voltage)
{
  m_voltage = t_voltage;
}

//! Function to get the value of the voltage source
/*
 * \return Voltage value at the node
 */
double Node::GetVoltage()
{
  return m_voltage;
}

bool Node::GetConnected()
{
  return m_connected;
}

void Node::SetConnected()
{
  m_connected =true;
}

bool Node::HasInstances()
{
  return m_has_instances;
}

std::vector<dbInst*> Node::GetInstances()
{
  return m_connected_instances;
}

void Node::AddInstance(dbInst* inst) 
{
  m_has_instances =true;
  m_connected_instances.push_back(inst);
}
